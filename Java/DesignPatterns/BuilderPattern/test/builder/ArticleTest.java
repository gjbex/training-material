/**
 * 
 */
package builder;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import builder.Article.ArticleBuilder;

/**
 * @author Geert Jan Bex
 *
 */
public class ArticleTest {

	private final String[] authors = {"Kaufman, Alice", "Dylan, Bob"};
	private final String title = "The influence of crypto-ysstem on popular music";
	private final String journal = "International Journal of Music Cognition and Marketing";
	private final int issue = 17;
	private final String pages = "25-37";
	private final int year = 2014;
	
	private Article.ArticleBuilder builder;
	
	@Before
	public void setUp() throws Exception {
		builder =  new Article.ArticleBuilder();
	}

	@Test
	public void testDefaultBuilder() {
		try {
			builder.setAuthors(authors);
			builder.setTitle(title);
			builder.setJournal(journal);
			builder.setIssue(issue);
			builder.setPages(pages);
			builder.setYear(year);
			Article article = builder.build();
			assertEquals(title, article.getTitle());
		} catch (InvalidArgumentException e) {
			fail("no " + e.getClass().getName() + " exception should be thrown");
		} catch (UninitializedArticleException e) {
			fail("no " + e.getClass().getName() + " exception should be thrown");
		}
	}

}
