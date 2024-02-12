package task;

import java.util.Objects;

public abstract class Task {
    private final int lineNumber;

    public Task(int lineNumber) {
        this.lineNumber = lineNumber;
    }

    abstract public void execute();
    public String toString(){
        return "Line: " + lineNumber;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Task task)) return false;
        return lineNumber == task.lineNumber;
    }

    @Override
    public int hashCode() {
        return Objects.hash(lineNumber);
    }
}
