/**
 * 
 */
package builder;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import com.sun.org.apache.xalan.internal.extensions.ExpressionContext;

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

	@Test(expected = InvalidArgumentException.class)
	public void testInvalidYear() throws Exception {
		builder.setYear(-1);
	}
	
	@Test(expected = UninitializedArticleException.class)
	public void testUninitialized() throws Exception {
		builder.setYear(2016).build();
	}

	@Test
	public void testNoOptionals() {
		try {
			builder.setAuthors(authors);
			builder.setTitle(title);
			builder.setJournal(journal);
			builder.setIssue(issue);
			builder.setPages(pages);
			builder.setYear(year);
			Article article = builder.build();
			assertEquals(title, article.getTitle());
			assertFalse(article.hasDOI());
			assertFalse(article.hasURL());
		} catch (InvalidArgumentException e) {
			fail("no " + e.getClass().getName() + " exception should be thrown");
		} catch (UninitializedArticleException e) {
			fail("no " + e.getClass().getName() + " exception should be thrown");
		}
	}

	@Test
	public void testOptionalDOI() {
		try {
			builder.setAuthors(authors);
			builder.setTitle(title);
			builder.setJournal(journal);
			builder.setIssue(issue);
			builder.setPages(pages);
			builder.setYear(year);
			builder.setDOI("10.1494549a");
			Article article = builder.build();
			assertEquals(title, article.getTitle());
			assertTrue(article.hasDOI());
			assertFalse(article.hasURL());
		} catch (InvalidArgumentException e) {
			fail("no " + e.getClass().getName() + " exception should be thrown");
		} catch (UninitializedArticleException e) {
			fail("no " + e.getClass().getName() + " exception should be thrown");
		}
	}

}