import gjb.demo.concurrentpi.PiComputer;

/**
 * Author:   Geert Jan Bex (geertjan.bex@uhasselt.be)
 * Createed: Oct 23, 2015
 */


/**
 * Driver class for computing pi.
 * 
 * @author Geert Jan Bex
 *
 */
public class PiDriver {

	public static void main(String[] args) {
		int nrProcesses = 1;
		int nrIntervals = 1;
		double deltaX = 1.0e-4;
		if (args.length > 0) {
			nrProcesses = Integer.parseInt(args[0]);
		}
		if (args.length > 1) {
			nrIntervals = Integer.parseInt(args[1]);
		}
		if (args.length > 2) {
			deltaX = Double.parseDouble(args[2]);
		}
		PiComputer piComputer = new PiComputer(nrProcesses);
		double pi = piComputer.compute(nrIntervals, deltaX);
		System.out.println("pi = " + pi);
		piComputer.finalize();
	}

}