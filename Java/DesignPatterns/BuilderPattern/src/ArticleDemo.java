import builder.UninitializedArticleException;

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
		classic.Article cArticle = new classic.Article(authors, title, journal, issue, pages, year);
		System.out.println("classic constructor:");
		System.out.println(cArticle);
		
		builder.Article.ArticleBuilder articleBuilder = new builder.Article.ArticleBuilder();
		articleBuilder.setAuthors(authors)
						.setTitle(title)
						.setJournal(journal)
						.setIssue(issue)
						.setPages(pages)
						.setYear(year);
		System.out.println("\nbuilder constructor:");
		try {
			builder.Article bArticle = articleBuilder.build();
			System.out.println(bArticle);
		} catch (UninitializedArticleException e) {
			System.err.println("article not fully initialized");
		}
	}

}