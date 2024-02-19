// This shows a simple usage of OpenCL

#include <utility>

#define CL_HPP_TARGET_OPENCL_VERSION 200
#define CL_HPP_MINIMUM_OPENCL_VERSION 200
#include <CL/opencl.hpp>

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <iterator>

void exitIfError(cl_int errorCode, char const* msg);
void errCallback(const char* errinfo, const void* private_info, size_t cb, void* user_data);
void printAllDevices();
void printDeviceProperties(cl::Device const& device);

int
main(void)
{
    cl_int err;
    printAllDevices();

    cl::Context context(CL_DEVICE_TYPE_GPU, nullptr, nullptr/*&errCallback*/, nullptr, &err);
    exitIfError(err, "Conext::Context()");

    std::vector<cl::Device> const devices = context.getInfo<CL_CONTEXT_DEVICES>();
    exitIfError(devices.size() > 0 ? CL_SUCCESS : -1, "devices.size() > 0");
    std::cerr << "Using " << devices.size() << " device(s)\n";
    for (cl::Device const& device : devices) {
        printDeviceProperties(device);
    }
    std::string prog(
        "#pragma OPENCL EXTENSION cl_khr_byte_addressable_store : enable\n"
        "__kernel void hello(__global int const* in, __global int* out, long n) {\n"
        "    int tid = get_global_id(0);\n"
        "    int sum = 0;\n"
        "    long i;\n"
        "    for(i = -5 ; i<=5 ; ++i) {\n"
        "        if(tid + i >= 0 && tid + i < n) {\n"
        "            sum += in[tid + i];\n"
        "        }\n"
        "    }\n"
        "    out[tid] = sum;\n"
        "}\n"
    );
    cl::Program::Sources sources{ prog };
    cl::Program program(context, sources);
    err = program.build(devices, "");
    exitIfError(err, "program build()");
    cl::Kernel kernel(program, "hello", &err);
    exitIfError(err, "Kernel::Kernel()");
    std::cerr << "Kernel built\n";

    cl::CommandQueue queue(context, devices[0], 0, &err);
    exitIfError(err, "CommandQueue::CommandQueue()");

    size_t const n = 100;
    cl::Buffer inputBuf(context, CL_MEM_READ_ONLY, n * 4, nullptr, &err);
    exitIfError(err, "Buffer::Buffer()");

    cl::Buffer outputBuf(context, CL_MEM_WRITE_ONLY, n * 4, nullptr, &err);
    exitIfError(err, "Buffer::Buffer()");

    err = kernel.setArg(0, inputBuf);
    exitIfError(err, "Kernel::setArg(0)");
    err = kernel.setArg(1, outputBuf);
    exitIfError(err, "Kernel::setArg(1)");
    err = kernel.setArg(2, int64_t(n));
    exitIfError(err, "Kernel::setArg(2)");

    std::vector<cl::Event> afterCopyIn(1);
    std::vector<cl::Event> afterKernelExec(1);
    std::vector<cl::Event> afterCopyOut(1);

    std::vector<cl_int> input(n, 1);
    err = queue.enqueueWriteBuffer(inputBuf, CL_FALSE, 0, 4 * input.size(), input.data(), nullptr, &afterCopyIn[0]);
    exitIfError(err, "ComamndQueue::enqueueWriteBuffer()");

    // afterCopyIn event will make the kernel execution wait for the buffer copy
    err = queue.enqueueNDRangeKernel(kernel,
        cl::NDRange(0),
        cl::NDRange(n),
        cl::NDRange(1),
        &afterCopyIn,
        &afterKernelExec[0]);
    exitIfError(err, "ComamndQueue::enqueueNDRangeKernel()");

    std::vector<cl_int> output(n, 0);
    // afterKernelExec event will make the buffer copy wait for the kernel execution
    err = queue.enqueueReadBuffer(outputBuf, CL_FALSE, 0, 4 * output.size(), output.data(), &afterKernelExec, &afterCopyOut[0]);
    exitIfError(err, "ComamndQueue::enqueueReadBuffer()");
    err = queue.flush();
    exitIfError(err, "ComamndQueue::flush()");

    // When we reach here, the commands are only enqueued, not necessarily executed
    // Therefore, what the following code writes is undefined
    std::cout << "Output (not ready): ";
    for (cl_int v : output) {
        std::cout << v << " ";
    }
    std::cout << "\n";

    // Wait for the copy from GPU buffers to host memory to be completed
    afterCopyOut[0].wait();
    std::cout << "Output (good): ";
    for (cl_int v : output) {
        std::cout << v << " ";
    }
    std::cout << "\n";
    return EXIT_SUCCESS;
}

const char* getErrorString(cl_int error)
{
    switch (error) {
        // run-time and JIT compiler errors
    case CL_SUCCESS:
        return "CL_SUCCESS";
    case CL_DEVICE_NOT_FOUND:
        return "CL_DEVICE_NOT_FOUND";
    case CL_DEVICE_NOT_AVAILABLE:
        return "CL_DEVICE_NOT_AVAILABLE";
    case CL_COMPILER_NOT_AVAILABLE:
        return "CL_COMPILER_NOT_AVAILABLE";
    case CL_MEM_OBJECT_ALLOCATION_FAILURE:
        return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
    case CL_OUT_OF_RESOURCES:
        return "CL_OUT_OF_RESOURCES";
    case CL_OUT_OF_HOST_MEMORY:
        return "CL_OUT_OF_HOST_MEMORY";
    case -7: return "CL_PROFILING_INFO_NOT_AVAILABLE";
    case -8: return "CL_MEM_COPY_OVERLAP";
    case -9: return "CL_IMAGE_FORMAT_MISMATCH";
    case -10: return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
    case -11: return "CL_BUILD_PROGRAM_FAILURE";
    case -12: return "CL_MAP_FAILURE";
    case -13: return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
    case -14: return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
    case -15: return "CL_COMPILE_PROGRAM_FAILURE";
    case -16: return "CL_LINKER_NOT_AVAILABLE";
    case -17: return "CL_LINK_PROGRAM_FAILURE";
    case -18: return "CL_DEVICE_PARTITION_FAILED";
    case -19: return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";

        // compile-time errors
    case -30: return "CL_INVALID_VALUE";
    case -31: return "CL_INVALID_DEVICE_TYPE";
    case -32: return "CL_INVALID_PLATFORM";
    case -33: return "CL_INVALID_DEVICE";
    case -34: return "CL_INVALID_CONTEXT";
    case -35: return "CL_INVALID_QUEUE_PROPERTIES";
    case -36: return "CL_INVALID_COMMAND_QUEUE";
    case -37: return "CL_INVALID_HOST_PTR";
    case -38: return "CL_INVALID_MEM_OBJECT";
    case -39: return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
    case -40: return "CL_INVALID_IMAGE_SIZE";
    case -41: return "CL_INVALID_SAMPLER";
    case -42: return "CL_INVALID_BINARY";
    case -43: return "CL_INVALID_BUILD_OPTIONS";
    case -44: return "CL_INVALID_PROGRAM";
    case -45: return "CL_INVALID_PROGRAM_EXECUTABLE";
    case -46: return "CL_INVALID_KERNEL_NAME";
    case -47: return "CL_INVALID_KERNEL_DEFINITION";
    case -48: return "CL_INVALID_KERNEL";
    case -49: return "CL_INVALID_ARG_INDEX";
    case -50: return "CL_INVALID_ARG_VALUE";
    case -51: return "CL_INVALID_ARG_SIZE";
    case -52: return "CL_INVALID_KERNEL_ARGS";
    case -53: return "CL_INVALID_WORK_DIMENSION";
    case -54: return "CL_INVALID_WORK_GROUP_SIZE";
    case -55: return "CL_INVALID_WORK_ITEM_SIZE";
    case -56: return "CL_INVALID_GLOBAL_OFFSET";
    case -57: return "CL_INVALID_EVENT_WAIT_LIST";
    case -58: return "CL_INVALID_EVENT";
    case -59: return "CL_INVALID_OPERATION";
    case -60: return "CL_INVALID_GL_OBJECT";
    case -61: return "CL_INVALID_BUFFER_SIZE";
    case -62: return "CL_INVALID_MIP_LEVEL";
    case -63: return "CL_INVALID_GLOBAL_WORK_SIZE";
    case -64: return "CL_INVALID_PROPERTY";
    case -65: return "CL_INVALID_IMAGE_DESCRIPTOR";
    case -66: return "CL_INVALID_COMPILER_OPTIONS";
    case -67: return "CL_INVALID_LINKER_OPTIONS";
    case -68: return "CL_INVALID_DEVICE_PARTITION_COUNT";

        // extension errors
    case -1000: return "CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR";
    case -1001: return "CL_PLATFORM_NOT_FOUND_KHR";
    case -1002: return "CL_INVALID_D3D10_DEVICE_KHR";
    case -1003: return "CL_INVALID_D3D10_RESOURCE_KHR";
    case -1004: return "CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR";
    case -1005: return "CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR";
    default: return "Unknown OpenCL error";
    }
}

void exitIfError(cl_int errorCode, char const* msg)
{
    if (errorCode != CL_SUCCESS) {
        fprintf(stderr, "OpenCL error at %s: %s(%d)\n", msg, getErrorString(errorCode), errorCode);
        exit(1);
    }
}

void errCallback(const char* errinfo, const void* private_info, size_t cb, void* user_data)
{
    fprintf(stderr, "OpenCL error callback: %s\n", errinfo);
    exit(1);
}

void printAllDevices()
{
    cl_int err;
    std::vector<cl::Platform> platformList;
    err = cl::Platform::get(&platformList);
    exitIfError(err, "cl::Platform::get()");

    std::cerr << "Found " << platformList.size() << " OpenCL platforms:\n";

    for (cl::Platform& platform : platformList) {
        std::cerr << "Platform name " << platform.getInfo<CL_PLATFORM_NAME>() <<
            ", vendor " << platform.getInfo<CL_PLATFORM_VENDOR>() << 
            ", version " << platform.getInfo<CL_PLATFORM_VERSION>() << "\n";
        std::vector<cl::Device> deviceList;
        err = platform.getDevices(CL_DEVICE_TYPE_ALL, &deviceList);
        exitIfError(err, "cl::Platform::getDevices()");
        std::cerr << "  platform has " << deviceList.size() << " device(s):\n";
        for (cl::Device& device : deviceList) {
            printDeviceProperties(device);
        }
    }
}

void printDeviceProperties(cl::Device const& device)
{
    std::cerr << "    type = " << device.getInfo<CL_DEVICE_TYPE>() << "\n";
    std::cerr << "    name = " << device.getInfo<CL_DEVICE_NAME>() << "\n";
    std::cerr << "    vendor = " << device.getInfo<CL_DEVICE_VENDOR>() << "\n";
    std::cerr << "    platform = " << device.getInfo<CL_DEVICE_PLATFORM>() << "\n";
    std::cerr << "    version = " << device.getInfo<CL_DEVICE_VERSION>() << "\n";
    std::cerr << "    driver-version = " << device.getInfo<CL_DRIVER_VERSION>() << "\n";
    std::cerr << "    max CU = " << device.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>() << "\n";
    std::cerr << "    max WI dimensions = " << device.getInfo<CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS>() << ":";
    for (auto dim : device.getInfo<CL_DEVICE_MAX_WORK_ITEM_SIZES>()) {
        std::cerr << " " << dim;
    }
    std::cerr << "\n";
    std::cerr << "    max WG size = " << device.getInfo<CL_DEVICE_MAX_WORK_GROUP_SIZE>() << "\n";
}