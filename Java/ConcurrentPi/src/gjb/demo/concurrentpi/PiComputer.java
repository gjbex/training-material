/**
 * Author:   Geert Jan Bex (geertjan.bex@uhasselt.be)
 * Createed: Oct 22, 2015
 */
package gjb.demo.concurrentpi;

import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

/**
 * Class that implements a parallel computation of pi.
 * 
 * @author Geert Jan Bex
 *
 */
public class PiComputer {

	private ExecutorService service;

	/**
	 * Create an object that will compute the value of pi using the given number of processes.
	 * @param nrProcesses
	 *        the number of processes that should be used to perform the computation
	 */
	public PiComputer(int nrProcesses) {
		this.service = new ThreadPoolExecutor(nrProcesses, nrProcesses, 10, TimeUnit.MINUTES,
				                              new LinkedBlockingQueue<Runnable>());
	}
	
	/**
	 * Compute pi given the number of intervals to divide [0.0, 1.0] in, and the deltaX value to use
	 * for the integration steps.
	 * @param nrIntervals
	 *        the number of intervals the computation should use
	 * @param deltaX 
	 *        resolution to use in the computation
	 */
	public double compute(int nrIntervals, double deltaX) {
		double pi = 0.0;
		double intervalWidth = 1.0/((double) nrIntervals);
		List<Future<Double>> futures = new LinkedList<Future<Double>>();
		for (int interval = 0; interval < nrIntervals; interval++) {
			double minX = interval*intervalWidth;
			double maxX = minX + intervalWidth;
			Callable<Double> task = new PartialPi(minX, maxX, deltaX);
			Future<Double> future = service.submit(task);
			futures.add(future);
		}
		for (Future<Double> future : futures) {
			try {
				pi += future.get();
			} catch (InterruptedException | ExecutionException e) {
				e.printStackTrace();
			}
		}
		return pi;
	}

	public void finalize() {
		service.shutdown();
	}

}