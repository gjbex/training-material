repo: create_repo.sh $(wildcard src/*.c) $(wildcard src/*.h)
	$(RM) -r repo
	./create_repo.sh

bisect: repo bisect.sh
	./bisect.sh

clean:
	$(RM) -r repo
