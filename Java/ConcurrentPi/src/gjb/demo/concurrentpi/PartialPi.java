/**
 * Author:   Geert Jan Bex (geertjan.bex@uhasselt.be)
 * Createed: Oct 22, 2015
 */
package gjb.demo.concurrentpi;

import java.util.concurrent.Callable;

/**
 * Class that implements a partial computation of pi in a subinterval of [0.0, 1.0]
 * 
 * @author Geert Jan Bex
 *
 */
class PartialPi implements Callable<Double> {

	private double minX;
	private double maxX;
	private double deltaX;
	private double result;

	/**
	 * Integrate the function over the specified interval [minX, maxX], where minX <= maxX using
	 * deltaX as step size.
	 * @param minX
	 *        left boundary of the interval to integrate over
	 * @param maxX
	 *        right boundary of the interval to integrate over
	 * @param deltaX
	 *        integration step size
	 */
	public PartialPi(double minX, double maxX, double deltaX) {
		this.minX = minX;
		this.maxX = maxX;
		this.deltaX = deltaX;
	}
	
	/**
	 * Return the result of the partial integration to obtain pi.
	 * @return result of the cmoputation
	 */
	public double getResult() {
		return result;
	}
	/* (non-Javadoc)
	 * @see java.lang.Runnable#run()
	 */
	@Override
	public Double call() {
		double x = minX;
		double sum = 0.0;
		while (x < maxX) {
			sum += piIntegrand(x);
			x += deltaX;
		}
		return sum*deltaX;
	}

	/**
	 * Function to integrate to obtain a value for pi
	 * @param x
	 * @return
	 */
	private static double  piIntegrand(double x) {
		return 4.0/(1.0 + x*x);
	}
}
