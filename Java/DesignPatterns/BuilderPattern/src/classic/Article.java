/**
 * 
 */
package classic;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * @author Geert Jan Bex
 *
 * This class represents an article as published in a scientific journal. The purpose is to illustrate
 * that constructors with many arguments lead to code that is error-prone, and that using the builder
 * pattern may be a better approach in such cases.
 */
public class Article {

	/**
	 * array of strings, each string representing an author of the aritcle
	 */
	private final List<String> authors = new ArrayList<String>();
	/**
	 * string representing an article's title
	 */
	private final String title;
	/**
	 * string representing an article's journal
	 */
	private final String journal;
	/**
	 * integer representing an article's issue number
	 */
	private final int issue;
	/**
	 * String representing the pages an article appears on
	 */
	private final String pages;
	/**
	 * integer representing the publication year of the article
	 */
	private final int year;

	public Article(String[] authors, String title, String journal, int issue,
			String pages, int year) throws InvalidArgumentException {
		if (!isValidAuthors(authors))
			throw new InvalidArgumentException("invalid authors");
		for (String author: authors)
			this.authors.add(author);
		if (!isValidTitle(title))
			throw new IllegalAccessError("invalid title");
		this.title = title;
		if (!isValidJournal(journal))
			throw new InvalidArgumentException("invalid journal");
		this.journal = journal;
		if (!isValidIssue(issue))
			throw new InvalidArgumentException("invalid issue");
		this.issue = issue;
		if (!isValidPages(pages))
			throw new InvalidArgumentException("invalid pages");
		this.pages = pages;
		if (!isValidYear(year))
			throw new InvalidArgumentException("invalid year");
		this.year = year;
	}

	/*
	 * What if we wanted to add two optional arguments, DOI and a URL where to find the article?
	 * We would need a constructor for four cases, niether DOI nor URL, one with DOI, one with
	 * URL, and finally one with both DOI and URL.  Note that the second and third can not be
	 * distinguished when both are represented by a String. 
	 */

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

	/**
	 * Method to retrieve the authors of an article.
	 * 
	 * @return the authors
	 */
	public Iterator<String> getAuthors() {
		return authors.iterator();
	}

	/**
	 * Method to return the title of an article.
	 * 
	 * @return the title
	 */
	public String getTitle() {
		return title;
	}

	/**
	 * Method to retrieve the journal name of an article.
	 * 
	 * @return the journal
	 */
	public String getJournal() {
		return journal;
	}

	/**
	 * Method to retrieve the journal's issue number the article was published in.
	 * 
	 * @return the issue
	 */
	public int getIssue() {
		return issue;
	}

	/**
	 * Method to retrieve the article's page range in the journal issue.
	 * @return the pages
	 */
	public String getPages() {
		return pages;
	}

	/**
	 * Method to retrieve the year the article was published in.
	 * 
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

}