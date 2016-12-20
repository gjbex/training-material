/**
 * 
 */
package builder;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * @author Geert Jan Bex
 *
 * This class represents an article as published in a scientific journal. The purpose is to illustrate
 * that constructors with many arguments can be avoided using the builder design pattern.
 */
public class Article {

	private final List<String> uninitializedAauthors = null;
	private final String uninitializedTitle = null;
	private final String uninitializedJournal = null;
	private final int uninitializedIssue = -1;
	private final String uninitializedPages = null;
	private final int uninitializedYear = -1;
	
	/**
	 * array of strings, each string representing an author of the aritcle
	 */
	private List<String> authors = uninitializedAauthors;
	/**
	 * string representing an article's title
	 */
	private String title = uninitializedTitle;
	/**
	 * string representing an article's journal
	 */
	private String journal = uninitializedJournal;
	/**
	 * integer representing an article's issue number
	 */
	private int issue = uninitializedIssue;
	/**
	 * String representing the pages an article appears on
	 */
	private String pages = uninitializedPages;
	/**
	 * integer representing the publication year of the article
	 */
	private int year = uninitializedYear;

	/**
	 * Default constructor, never to be used outside of the ArticleBuilder inner class.
	 */
	private Article() {
		super();
	}

	/**
	 * @return the authors
	 */
	public Iterator<String> getAuthors() {
		return authors.iterator();
	}

	/**
	 * @return the title
	 */
	public String getTitle() {
		return title;
	}

	/**
	 * @return the journal
	 */
	public String getJournal() {
		return journal;
	}

	/**
	 * @return the issue
	 */
	public int getIssue() {
		return issue;
	}

	/**
	 * @return the pages
	 */
	public String getPages() {
		return pages;
	}

	/**
	 * @return the year
	 */
	public int getYear() {
		return year;
	}

	/* (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		StringBuilder authorsBuilder = new StringBuilder();
		Iterator<String> iter = getAuthors();
		authorsBuilder.append(iter.next());
		while (iter.hasNext())
			authorsBuilder.append("; ").append(iter.next());
		StringBuilder builder = new StringBuilder();
		builder.append("Authors: ").append(authorsBuilder.toString())
		        .append("\nTitle: ").append(getTitle())
		        .append("\nJournal: ").append(getJournal())
		        .append("\nIssue: ").append(getIssue())
		        .append("\nPages: ").append(getPages())
		        .append("\nYear: ").append(getYear());
		return builder.toString();
	}

	public static class ArticleBuilder {
		
		/**
		 * article under construction by the builder
		 */
		private Article article;

		/**
		 * Constructor for the builder object.
		 */
		public ArticleBuilder() {
			this.article = new Article();
		}

		/**
		 * Method to set authors of a journal article. The array should not be
		 * null, contain at least one  element, and all elements should be non-null and non-empty.
		 * 
		 * @param authors String array representing the authors
		 * @return the article builder object
		 * @throws InvalidArgumentException 
		 */
		public ArticleBuilder setAuthors(String[] authors) throws InvalidArgumentException {
			if (!Article.isValidAuthors(authors))
				throw new InvalidArgumentException("invalid authors");
			this.article.authors = new ArrayList<String>();
			for (String author: authors)
				this.article.authors.add(author);
			return this;
		}
		
		/**
		 * Method to set title of a journal article. The string  should be non-null and non-empty.
		 * 
		 * @param authors String representing the title
		 * @return the article builder object
		 * @throws InvalidArgumentException 
		 */
		public ArticleBuilder setTitle(String title) throws InvalidArgumentException {
			if (!Article.isValidTitle(title))
				throw new InvalidArgumentException("invalid title");
			this.article.title = title;
			return this;
		}
		
		/**
		 * Method to set journal of a journal article. The string  should be non-null and non-empty.
		 * 
		 * @param authors String representing the journal name
		 * @return the article builder object
		 * @throws InvalidArgumentException 
		 */
		public ArticleBuilder setJournal(String journal) throws InvalidArgumentException {
			if (!Article.isValidJournal(journal))
				throw new InvalidArgumentException("invalid journal");
			this.article.journal = journal;
			return this;
		}
		
		/**
		 * Method to set the issue of a journal article. The issue should be positive.
		 * 
		 * @param authors String representing the journal issue
		 * @return the article builder object
		 * @throws InvalidArgumentException 
		 */
		public ArticleBuilder setIssue(int issue) throws InvalidArgumentException {
			if (!Article.isValidIssue(issue))
				throw new InvalidArgumentException("invalid issue");
			this.article.issue = issue;
			return this;
		}
		
		/**
		 * Method to set the pages of a journal article. The string  should be non-null and non-empty.
		 * 
		 * @param authors String representing the articles pages
		 * @return the article builder object
		 * @throws InvalidArgumentException 
		 */
		public ArticleBuilder setPages(String pages) throws InvalidArgumentException {
			if (!Article.isValidPages(pages))
				throw new InvalidArgumentException("invalid pages");
			this.article.pages = pages;
			return this;
		}
		
		/**
		 * Method to set the year of a journal article. The year should be strictly positive.
		 * 
		 * @param authors String representing the journal issue
		 * @return the article builder object
		 * @throws InvalidArgumentException 
		 */
		public ArticleBuilder setYear(int year) throws InvalidArgumentException {
			if (!Article.isValidYear(year))
				throw new InvalidArgumentException("invalid year");
			this.article.year = year;
			return this;
		}
		
		/**
		 * Method to build the article constructing using the builder object.
		 * @return the Article object constructed by the builder.
		 * @throws UninitializedArticleException indicates that not all attributes of the
		 *         article have been initialized using the builder.
		 */
		public Article build() throws UninitializedArticleException {
			if (!this.article.isInitialized())
				throw new UninitializedArticleException();
			return this.article;
		}
		
	}
	
	/**
	 * Method to validate an array that represents authors of a journal article. The array should not be
	 * null, contain at least one  element, and all elements should be non-null and non-empty.
	 * 
	 * @param authors String array representing authors
	 * @return true if the array of authors is valid
	 */
	private static boolean isValidAuthors(String[] authors) {
		if (authors == null || authors.length == 0)
			return false;
		for (String author: authors)
			if (!isValidStringAttribute(author))
				return false;
		return true;
	}
	
	/**
	 * Method to validate a string that represents the title of a journal article. This string should
	 * not be null, and not be empty.
	 * 
	 * @param title String representting an article title
	 * @return true if the string is a valid title
	 */
	private static boolean isValidTitle(String title) {
		return isValidStringAttribute(title);
	}

	/**
	 * Method to check whether a journal name is valid
	 * 
	 * @param journal String representing an article's journal name
	 * @return true if valid
	 */
	private static boolean isValidJournal(String journal) {
		return isValidStringAttribute(journal);
	}

	/**
	 * Method to check whether an article's journal issue is valid, i.e., whether it is
	 * positive.
	 * 
	 * @param issue integer representing the jounral issue of the article
	 * @return
	 */
	private static boolean isValidIssue(int issue) {
		return issue >= 0;
	}
	
	/**
	 * Method to check whether the article's publication year is valid, i.e., whether it is strictly
	 * positive.
	 *  
	 * @param year integer representing the publication year of an article
	 * @return true if valid
	 */
	private static boolean isValidYear(int year) {
		return year > 0;
	}

	/**
	 * Method to check whether a page range for an article is valid, i.e., it should not be null, and
	 * it can be either a number, or a range, e.g., 5-12.
	 * 
	 * @param pages String representing the article's page range
	 * @return true if valid
	 */
	private static boolean isValidPages(String pages) {
		return pages != null && pages.matches("\\d+(?:-\\d+)");
	}
	
	/**
	 * Method to check whether a given string is a valid attribute, i.e., if it is not null, and not
	 * empty
	 * 
	 * @param stringAttr String to validate
	 * @return true if valid
	 */
	private static boolean isValidStringAttribute(String stringAttr) {
		return stringAttr != null && stringAttr.length() > 0;
	}

	private boolean isInitialized() {
		return this.authors != uninitializedAauthors &&
				this.title != uninitializedTitle &&
				this.journal != uninitializedJournal &&
				this.issue != uninitializedIssue &&
				this.pages != uninitializedPages &&
				this.year != uninitializedYear;
	}

}