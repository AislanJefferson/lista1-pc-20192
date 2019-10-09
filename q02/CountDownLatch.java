public class CountDownLatch{

    private int count;
    private final Object objSync = new Object();

    public CountDownLatch(int count) {
           synchronized(objSync){
              this.count=count;
           }    
    }

    public void await() throws InterruptedException {
           synchronized(objSync){
              while(count>0){
                 objSync.wait();
              }
           }
           
    }

    public void countDown() {
           synchronized(objSync){
              count--;
              if(count == 0){
                     objSync.notifyAll();
              }   
           }
    }
}
