import classic.InvalidArgumentException;

/**
 * 
 */

/**
 * @author lucg5005
 *
 */
public class ArticleDemo {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		String[] authors = {"Kaufman, Alice", "Dylan, Bob"};
		String title = "The influence of crypto-ysstem on popular music";
		String journal = "International Journal of Music Cognition and Marketing";
		int issue = 17;
		String pages = "25-37";
		int year = 2014;
		try {
			classic.Article cArticle = new classic.Article(authors, title, journal, issue, pages, year);
			System.out.println("classic constructor:");
			System.out.println(cArticle);
		} catch (InvalidArgumentException e) {
			System.err.println("error: " + e.getMessage());
		}
		
		try {
			builder.Article.ArticleBuilder articleBuilder = new builder.Article.ArticleBuilder();
			articleBuilder.setAuthors(authors)
						.setTitle(title)
						.setJournal(journal)
						.setIssue(issue)
						.setPages(pages)
						.setYear(year);
			System.out.println("\nbuilder constructor:");
			builder.Article bArticle = articleBuilder.build();
			System.out.println(bArticle);
		} catch (builder.UninitializedArticleException e) {
			System.err.println("article not fully initialized");
		} catch (builder.InvalidArgumentException e) {
			System.err.println("error: " + e.getMessage());
		}
	}

}