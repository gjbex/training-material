all: batch_run_notebook convert_to_md batch_run_md

batch_run_notebook: notebook_example.nbconvert.ipynb

notebook_example.nbconvert.ipynb: notebook_example.ipynb
	jupyter nbconvert --to notebook --execute \
		--ExecutePreprocessor.timeout=600 \
		$<

convert_to_md: notebook_example.md

notebook_example.md: notebook_example.ipynb
	notedown --to markdown --strip $< > $@

batch_run_md: example_md.ipynb

example_md.ipynb: example.md
	notedown --run $< > $@

clean:
	$(RM) notebook_example.nbconvert.ipynb
	$(RM) notebook_example.md
	$(RM) example_md.ipynb
