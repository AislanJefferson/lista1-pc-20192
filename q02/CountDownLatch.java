class CountDownLatch{
    
    private int count;
    
    public CountDownLatch() {
	// TODO Auto-generated constructor stub
    }
    
    private void await() {
	while(count != 0) {
	    synchronized(this) {
		wait();
	    }
	}
    }
}
