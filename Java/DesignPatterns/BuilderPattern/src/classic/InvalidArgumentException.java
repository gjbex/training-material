package classic;

/**
 * @author Geert Jan Bex
 *
 */
public class InvalidArgumentException extends Exception {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private String message;

	public InvalidArgumentException(String message) {
		this.message = message;
	}
	
	public String getMessage() {
		return message;
	}

}