// This shows a simple usage of OpenCL, but with two-dimensional ranges of kernels

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

const std::string hw("Hello World\n");

void exitIfError(cl_int errorCode, char const* msg);
void errCallback(const char* errinfo, const void* private_info, size_t cb, void* user_data);

int
main(void)
{
    cl_int err;
    std::vector<cl::Platform> platformList;
    err = cl::Platform::get(&platformList);
    exitIfError(platformList.empty() ? CL_PLATFORM_NOT_FOUND_KHR : err, "cl::Platform::get()");

    std::vector<cl::Device> deviceList;
    err = platformList[0].getDevices(CL_DEVICE_TYPE_GPU, &deviceList);
    exitIfError(deviceList.empty() ? CL_DEVICE_NOT_FOUND : err, "cl::Platform::getDevices()");

    cl::Context context(CL_DEVICE_TYPE_GPU, nullptr, &errCallback, nullptr, &err);
    exitIfError(err, "Conext::Context()");

    std::vector<cl::Device> const devices = context.getInfo<CL_CONTEXT_DEVICES>();
    exitIfError(devices.size() > 0 ? CL_SUCCESS : -1, "devices.size() > 0");
    std::cerr << "Found " << devices.size() << " device(s)\n";
    for (cl::Device const& device : devices) {
        std::cerr << "  type = " << device.getInfo<CL_DEVICE_NAME>() << "\n";
    }
    std::string prog(
        "#pragma OPENCL EXTENSION cl_khr_byte_addressable_store : enable\n"
        "__kernel void hello(__global int const* in, __global int* out, long n) {\n"
        "    int tid1 = get_global_id(0);\n" // takes the index on the first dimension
        "    int tid2 = get_global_id(1);\n" // takes the index on the second dimension
        "    int sum = 0;\n"
        "    long i, j;\n"
        "    for(i = -1 ; i<=1 ; ++i) {\n"
        "        if(tid1 + i >= 0 && tid1 + i < n) {\n"
        "            for(j = -1 ; j<=1 ; ++j) {\n"
        "                if(tid2 + j >= 0 && tid2 + j < n) {\n"
        "                    sum += in[(tid1 + i)*n + (tid2 + j)];\n"
        "                }\n"
        "            }\n"
        "        }\n"
        "    }\n"
        "    out[tid1*n + tid2] = sum;\n"
        "}\n"
    );
    cl::Program::Sources source{ prog };
    cl::Program program(context, source);
    err = program.build(devices, "");
    exitIfError(err, "program build()");
    cl::Kernel kernel(program, "hello", &err);
    exitIfError(err, "Kernel::Kernel()");
    std::cerr << "Kernel built\n";

    cl::CommandQueue queue(context, devices[0], 0, &err);
    exitIfError(err, "CommandQueue::CommandQueue()");

    size_t const n = 10;
    cl::Buffer inputBuf(context, CL_MEM_READ_ONLY, n * n * 4, nullptr, &err);
    exitIfError(err, "Buffer::Buffer()");

    cl::Buffer outputBuf(context, CL_MEM_WRITE_ONLY, n * n * 4, nullptr, &err);
    exitIfError(err, "Buffer::Buffer()");

    err = kernel.setArg(0, inputBuf);
    exitIfError(err, "Kernel::setArg(0)");
    err = kernel.setArg(1, outputBuf);
    exitIfError(err, "Kernel::setArg(1)");
    err = kernel.setArg(2, int64_t(n));
    exitIfError(err, "Kernel::setArg(2)");

    std::vector<cl::Event> afterCopyIn(1);
    std::vector<cl::Event> afterKernelExec(1);

    std::vector<cl_int> input(n * n, 1);
    err = queue.enqueueWriteBuffer(inputBuf, CL_FALSE, 0, 4 * input.size(), input.data(), nullptr, &afterCopyIn[0]);
    exitIfError(err, "ComamndQueue::enqueueWriteBuffer()");

    err = queue.enqueueNDRangeKernel(kernel,
        cl::NDRange(0, 0),
        cl::NDRange(n, n), // execute n*n instances
        cl::NDRange(1, 1),
        &afterCopyIn,
        &afterKernelExec[0]);
    exitIfError(err, "ComamndQueue::enqueueNDRangeKernel()");

    std::vector<cl_int> output(n * n, 0);
    err = queue.enqueueReadBuffer(outputBuf, CL_FALSE, 0, 4 * output.size(), output.data(), &afterKernelExec);
    exitIfError(err, "ComamndQueue::enqueueReadBuffer()");
    err = queue.flush();
    exitIfError(err, "ComamndQueue::flush()");

    afterKernelExec[0].wait();
    std::cout << "Output (good):\n";
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            std::cout << output[i * n + j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "----\n";
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