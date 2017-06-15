# BuilderPattern
This is an illustration of the builder design pattern.

## What is it?
1. `src/classic/Article.java`: classic implementation with a constructure signature that is
	quite involved, and hence error prone.
1. `src/builder/Article.java`: implementation using the builder pattern. The Article class
	has a static inner class that implements its builder. Article attributes are set on the builder,
	which returns the actual object when it has checked construction is complete.
1. `src/builder/UninitializedArticleException.java`: exception thrown when an Article
	is built that is not yet completely configured.