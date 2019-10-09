package q04;

import java.util.Collection;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class CacheMap<K, V> implements Map<K, V> {
	private HashMap<K, V> cache;
	private Map<K, V> remoteMap;

	private ReadWriteLock locks;

	//
	private final int MAX_TTL;
	private volatile int ttlCounter; // NAO usado atualmente
	private final int CACHE_MAX_SIZE;
	private AtomicInteger currentCacheSize; // Conta o numero de entradas atualmente no cache

	private Timer timer;

	// QUERIA FAZER ALGO ESTILO TIMESTAMP
	private long lastChangedLocally = 0;
	private long lastFlushedToRemote = 0;

	private class Flusher implements Runnable {
		AtomicInteger counter;

		public Flusher() {
			counter = new AtomicInteger(0);
		}

		private void flush() {
			System.out.println("Fazendo flush!");
			remoteMap.putAll(cache);
			cache.clear();
			lastFlushedToRemote = System.currentTimeMillis();
			System.out.println("Flush efetuado!");
			counter.set(0);
		}

		@Override
		public void run() {
			// TODO Auto-generated method stub

			while (counter.getAndIncrement() < MAX_TTL) {
				try {
					System.out.println(counter.toString());
					synchronized (this) {
						this.wait();
					}
				} catch (InterruptedException e) {
					System.out.println("Fechando...");
				}
			}
			this.flush();
			this.run();
		}
	}

	private Flusher flusher;

	public CacheMap(Map<K, V> remoteMap, int cacheSize, int ttl) {
		this.locks = new ReentrantReadWriteLock(true);
		this.remoteMap = remoteMap;
		this.MAX_TTL = ttl;
		this.CACHE_MAX_SIZE = cacheSize;
		this.currentCacheSize = new AtomicInteger(0);
		flusher = new Flusher();
		Thread t1 = new Thread(flusher);
		t1.start();
		timer = new Timer(true);
		// Vai ficar rodando a cada 1 segundo
		timer.scheduleAtFixedRate(new TimerTask() {

			@Override
			public void run() {
				synchronized (flusher) {
					flusher.notify();
				}

			}
		}, new Date(), 1000);
		cache = new HashMap<K, V>(cacheSize);
	}

	@Override
	public int size() {
		// TODO FAZER
		return 0;
	}

	@Override
	public boolean isEmpty() {
		// TODO FAZER
		return false;
	}

	@Override
	public boolean containsKey(Object key) {
		// TODO FAZER
		// this.cache.containsKey(key) || this.remoteMap.containsKey(key);
		return false;
	}

	@Override
	public boolean containsValue(Object value) {
		// TODO FAZER
		// this.cache.containsValue(value) || this.remoteMap.containsValue(value);
		return false;
	}

	@Override
	public V get(Object key) {
		// TODO FAZER
		V value = null;
		// Se tiver nao tiver no cache entao verifica se tah remotamente e se
		// tiver coloca no cache
		if (!this.cache.containsKey(key)) {
			if (this.remoteMap.containsKey(key)) {
				value = this.remoteMap.get(key);
				// INICIO PARTE OPCIONAL DE ADICIONAR DADO LIDO AO CACHE
				this.cache.put((K) key, value);
				currentCacheSize.incrementAndGet();
				// FIM PARTE OPCIONAL
			}
		} else {
			value = this.cache.get(key);
		}
		return value;
	}

	@Override
	public V put(K key, V value) {
		flusher.flush();
		// TODO FAZER
		return null;
	}

	@Override
	public V remove(Object key) {
		// TODO FAZER
		return null;
	}

	@Override
	public void clear() {
		// TODO FAZER

	}

	@Override
	public void putAll(Map<? extends K, ? extends V> m) {
		// NAO PRECISA FAZER

	}

	@Override
	public Set<K> keySet() {
		// NAO PRECISA FAZER
		return null;
	}

	@Override
	public Collection<V> values() {
		// NAO PRECISA FAZER
		return null;
	}

	@Override
	public Set<Entry<K, V>> entrySet() {
		// NAO PRECVISA FAZER
		return null;
	}

}
