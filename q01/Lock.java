import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.LockSupport;

public class Lock {
    private List<Thread> fila = new ArrayList<Thread>();
    private volatile boolean locked = false;

    public void lock() {
	if (locked) {
	    fila.add(Thread.currentThread());
	    LockSupport.park();
	}
	locked = true;
    }

    public void unlock() {
	locked = false;
	if (!fila.isEmpty()) {
	    Thread threadToRun = fila.remove(0);
	    LockSupport.unpark(threadToRun);
	}

    }
}