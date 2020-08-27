#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct tweet_{
	char **content;
	char **tagged_people;
	char **hashtags;
}tweet;

FILE *fusers, *fusers2;
tweet tweetEntered = {NULL,NULL,NULL};
int str_index_content = 0, str_index_tag = 0, str_index_hashtag = 0;

void print_file(FILE *fp)
{
    char ch;
    while((ch = fgetc(fp)) != EOF )
    {
        printf("%c", ch);
    }
}

int stringCompare(const char *s1, const char *s2){
  int ret = 0;

  while (!(ret = *(unsigned char *) s1 - *(unsigned char *) s2) && *s2) ++s1, ++s2;

  if (ret < 0){
    ret = -1;
  }
  else if (ret > 0){
  	ret = 1 ;
  }

  return ret;
}

char *stringCopy(char *d, const char *s)
{
   char *dest = d;
   while (*s)
   {
       *d++ = *s++;
   }
   *d = 0;
   return dest;
}

char *stringNumCopy(char *dest, const char *source, size_t n) {
    size_t i;
    for (i = 0; i < n && source[i] != '\0'; i++) {
        dest[i] = source[i];
    }
    dest[i] = '\0';
    return dest;
}

char *stringCat (char *dest, const char *src)
{
  stringCopy(dest + strlen (dest), src);
  return dest;
}

//revise checkUsername
int checkUsername(char *username){

	char *buff = (char *) malloc(100 * sizeof(char));
	int ctr = 0, val = 0;

	fusers = fopen("users.txt", "r");
	while (!feof(fusers)){
		fscanf(fusers, "%s", buff);
		int cmp = stringCompare(buff, username);
		if (cmp == 0){
			ctr = 1;
		}
	}

	//username exists
	if (ctr == 1){
		val = 0;
	}

	//username does not exist
	else{
		val = -1;
	}

	if(buff != NULL){
		free(buff);
		buff = NULL;
	}

	fclose (fusers);
	return val;
}

void deleteUsername(char *username){
		int i = 0, counter = 1;
		char ch = 'a', *buff = (char *) malloc(100 * sizeof(char)), *str = (char *) malloc(100 *sizeof(char));
		int del_line_no = 0, line_no = 0;

		//remove ".txt" from variable "username"
		while (username[i] != '.'){
			i++;
		}
		while(username[i] != '\0'){
			username[i] = '\0';
			i++;
		}

    //open text file that contains the list of logged-in users
    fusers = fopen("users.txt", "r+");

    //delete the line from the content
    while (!feof(fusers)){
        fscanf(fusers, "%s", buff);
        int cmp = stringCompare(buff, username);
        if (cmp == 0){
            del_line_no = counter;
            break;
        }
        counter++;
    }

    // rewind(fusers);
    fusers2 = fopen("replica.txt", "w+");
    while( fgets(str, 99, fusers) != NULL )
    {
        line_no++;
        if(line_no != del_line_no)
        {
            fputs(str, fusers2);
        }
    }

    fclose(fusers);
    fclose(fusers2);
    remove("users.txt");
    rename("replica.txt", "users.txt");


		if(buff != NULL)
		{
			free(buff);
			buff = NULL;
		}
		if(str != NULL)
		{
			free(str);
			str = NULL;
		}
}

int parseTweet(char *tweet){

	int string_len = 0, j = 0, val = 1;

	for (int i = 0; tweet[i] != '\0'; i++){

		if(tweet[i] == '#'){
			tweetEntered.hashtags = realloc(tweetEntered.hashtags, sizeof(char *) * (str_index_hashtag + 1));

			if (tweetEntered.hashtags == NULL){
				puts("Error - Memory was not allocated");
				val = 0;
				break;
			}

			for(j = i; tweet[j] != '\0'; j++)
			{
				if((tweet[j] == ' ') || (tweet[j] == '\n'))
				{
					string_len = j-i;
					tweetEntered.hashtags[str_index_hashtag] = malloc(sizeof(char) * (string_len + 1));

					if (tweetEntered.hashtags == NULL){
						puts("Error - Memory was not allocated");
						val = 0;
					}

					stringNumCopy(tweetEntered.hashtags[str_index_hashtag], &tweet[i],  string_len);
					tweetEntered.hashtags[str_index_hashtag][string_len] = '\0';

					// printf("hashtags (%d): %s \n", str_index_hashtag, tweetEntered.hashtags[str_index_hashtag]);
					break;
				}
			}
			if(tweet[j] == '\0') // Catch the last word in the string
			{
				string_len = j-i;
				tweetEntered.hashtags[str_index_hashtag] = malloc(sizeof(char) * (string_len + 1));

				if (tweetEntered.hashtags == NULL){
					puts("Error - Memory was not allocated");
					val = 0;
				}

				stringNumCopy(tweetEntered.hashtags[str_index_hashtag], &tweet[i],  string_len);
				tweetEntered.hashtags[str_index_hashtag][string_len] = '\0';

				// printf("hashtags (%d): %s \n", str_index_hashtag, tweetEntered.hashtags[str_index_hashtag]);
			}

			str_index_hashtag++; // Make sure index count is correct
			i = j;
		}

		else if(tweet[i] == '@'){
			tweetEntered.tagged_people = realloc(tweetEntered.tagged_people, sizeof(char *) * (str_index_tag + 1));

			if (tweetEntered.tagged_people == NULL){
				puts("Error - Memory was not allocated");
				val = 0;
				break;
			}

			for(j = i; tweet[j] != '\0'; j++)
			{
				if((tweet[j] == ' ') || (tweet[j] == '\n'))
				{
					string_len = j-i;
					tweetEntered.tagged_people[str_index_tag] = malloc(sizeof(char) * (string_len + 1));

					if (tweetEntered.tagged_people == NULL){
						puts("Error - Memory was not allocated");
						val = 0;
					}

					stringNumCopy(tweetEntered.tagged_people[str_index_tag], &tweet[i],  string_len);
					tweetEntered.tagged_people[str_index_tag][string_len] = '\0';

					// Make sure username is valid
					if (checkUsername(&tweetEntered.tagged_people[str_index_tag][1]) != 0){
						val = 0;
					}

					// printf("tagged_people (%d): %s \n", str_index_tag, tweetEntered.tagged_people[str_index_tag]);
					break;
				}
			}
			if(tweet[j] == '\0') // Catch the last word in the string
			{
				string_len = j-i;
				tweetEntered.tagged_people[str_index_tag] = malloc(sizeof(char) * (string_len + 1));

				if (tweetEntered.tagged_people == NULL){
					puts("Error - Memory was not allocated");
					val = 0;
				}

				stringNumCopy(tweetEntered.tagged_people[str_index_tag], &tweet[i],  string_len);
				tweetEntered.tagged_people[str_index_tag][string_len] = '\0';

				// Make sure username is valid
				if (checkUsername(&tweetEntered.tagged_people[str_index_tag][1]) != 0){
					val = 0;
				}

				// printf("tagged_people (%d): %s \n", str_index_tag, tweetEntered.tagged_people[str_index_tag]);
			}

			str_index_tag++; // Make sure index count is correct
			i = j;
		}

		// Grab content (but skip leading spaces)
		else if(tweet[i] != ' ')
		{
			tweetEntered.content = realloc(tweetEntered.content, sizeof(char *) * (str_index_content + 1));

			if (tweetEntered.content == NULL){
				puts("Error - Memory was not allocated");
				val = 0;
				break;
			}

			for(j = i; tweet[j] != '\0'; j++)
			{
				if((tweet[j] == '@') || (tweet[j] == '#'))
				{
					string_len = j-i;
					// Remove trailing space
					if(tweet[j-1] == ' ')
					{
						string_len -= 1;
					}

					tweetEntered.content[str_index_content] = malloc(sizeof(char) * (string_len + 1));

					if (tweetEntered.content == NULL){
						puts("Error - Memory was not allocated");
						val = 0;
					}

					stringNumCopy(tweetEntered.content[str_index_content], &tweet[i],  string_len);
					tweetEntered.content[str_index_content][string_len] = '\0';

					//printf("content (%d): %s \n", str_index_content, tweetEntered.content[str_index_content]);
					break;
				}
			}
			if(tweet[j] == '\0') // Catch the last word in the string
			{
				string_len = j-i;

				tweetEntered.content[str_index_content] = malloc(sizeof(char) * (string_len + 1));

				if (tweetEntered.content == NULL){
					puts("Error - Memory was not allocated");
					val = 0;
				}

				stringNumCopy(tweetEntered.content[str_index_content], &tweet[i],  string_len);
				tweetEntered.content[str_index_content][string_len] = '\0';

				//printf("content (%d): %s \n", str_index_content, tweetEntered.content[str_index_content]);
			}

			str_index_content++; // Make sure index count is correct
			i = j - 1; // Set i to index of @ or # and not the following character
		}

	}

	return val;
}

void saveTweet(char *username){

	FILE ** tweetFile;
	int i, j = 0;
	char *ext = ".txt\0";
	char *usernameTextFile = NULL;

	// printf("number of tagged people >> %d\n", str_index_tag);
	//if there are no people tagged, do this
	if (str_index_tag == 0){
		tweetFile = (FILE **) malloc(sizeof(FILE*));
		tweetFile[0] = fopen("public_tweets.txt", "a");
	}

	//if there are people tagged, do this
	else{
		tweetFile = (FILE **) malloc(sizeof(FILE*) * str_index_tag);

		if (tweetFile == NULL){
			puts("Error - Memory not allocated");
			return;
		}

		for (i = 0; i < str_index_tag; i++){
			int len = strlen(&tweetEntered.tagged_people[i][1]);
			usernameTextFile = (char *) malloc(sizeof(char) * (len+4));

			if (usernameTextFile == NULL){
				puts("Error - Memory not allocated");
				return;
			}

			stringCopy(usernameTextFile, &tweetEntered.tagged_people[i][1]);
			stringCopy(&usernameTextFile[len], ext);

			tweetFile[i] = fopen(usernameTextFile, "a");

			free(usernameTextFile);
		}
	}

	//remove the ".txt"
	while (username[j] != '.'){
		j++;
	}
	while(username[j] != '\0'){
		username[j] = '\0';
		j++;
	}

	if (str_index_tag == 0){
		for (int i = 0; i <= str_index_tag; i++){

		int len = strlen(username);
		fprintf(tweetFile[i], "%s", username);

		for (int x = 0; x<str_index_content; x++){
			fprintf(tweetFile[i], ",%s",tweetEntered.content[x]);
		}

		for (int x = 0; x<str_index_hashtag; x++){
			fprintf(tweetFile[i], ",%s", tweetEntered.hashtags[x]);
		}

		fprintf(tweetFile[i], "\n");
		fclose(tweetFile[i]);
		}
	}

	else{
		for (int i = 0; i < str_index_tag; i++){

		int len = strlen(username);
		fprintf(tweetFile[i], "%s", username);

		for (int x = 0; x<str_index_content; x++){
			fprintf(tweetFile[i], ",%s",tweetEntered.content[x]);
		}

		for (int x = 0; x<str_index_tag; x++){
			fprintf(tweetFile[i], ",%s", tweetEntered.tagged_people[x]);
		}

		for (int x = 0; x<str_index_hashtag; x++){
			fprintf(tweetFile[i], ",%s", tweetEntered.hashtags[x]);
		}

		fprintf(tweetFile[i], "\n");
		fclose(tweetFile[i]);
		}
	}

	stringCat(username, ".txt");

	free(tweetFile);
}

void viewNotifications(char *username){

	FILE * input;
	input = fopen(username, "r+");
	char *found, *string = (char*) malloc(sizeof(char)*500);
	int check = 0, counter = 0;

	while (!feof(input)){

			fgets(string, 500, input);
			found = strtok(string,",");

			if( found==NULL){
					puts("[ERROR] File empty or no separators found.\n");
					return;
			}

			while(found){
					// print the name of the person who sent the tweet using the format @name:
					if (check == 0 && !feof(input)){
							 printf("@%s:\n",found);
							 found = strtok(NULL,",");
							 check = 1;
					}

					// print the tweet itself of the hashtags
					else {
							if (!feof(input)){
									printf("%s ",found);
							}
							found = strtok(NULL,",");
							// when the line ends, set check = 0 to print the name using the format @name:
							if (found==NULL){
								puts("");
								check = 0;
							}
					}
			}
	}

	free(string);
	fclose(input);

}

void viewWall(){

    FILE * input;
    input = fopen("public_tweets.txt", "r+");
    char *found, *string = (char*) malloc(sizeof(char)*500);
    int check = 0, counter = 0;

    while (!feof(input)){

        fgets(string, 500, input);
        found = strtok(string,",");

        if( found==NULL){
            puts("[ERROR] No separators found.\n");
            return;
        }

        while(found){
						// print the name of the person who sent the tweet using the format @name:
            if (check == 0 && !feof(input)){
                 printf("@%s:\n",found);
                 found = strtok(NULL,",");
								 check = 1;
            }

						// print the tweet itself of the hashtags
            else {
								if (!feof(input)){
										printf("%s ",found);
								}
								found = strtok(NULL,",");
								// when the line ends, set check = 0 to print the name using the format @name:
								if (found==NULL){
									puts("");
									check = 0;
								}
            }
        }
    }

    free(string);
    fclose(input);
}

void freeGlobalTweet(){

	int i;
	for (i = 0; i < str_index_content; i++){
		if(tweetEntered.content[i] != NULL){
			free(tweetEntered.content[i]);
			tweetEntered.content[i] = NULL;
		}
	}
	if(tweetEntered.content != NULL){
		free(tweetEntered.content);
		tweetEntered.content = NULL;
	}

	for (i = 0; i < str_index_tag; i++){
		if(tweetEntered.tagged_people[i] != NULL){
			free(tweetEntered.tagged_people[i]);
			tweetEntered.tagged_people[i] = NULL;
		}
	}
	if(tweetEntered.tagged_people != NULL){
		free(tweetEntered.tagged_people);
		tweetEntered.tagged_people = NULL;
	}

	for (i = 0; i < str_index_hashtag; i++){
		if(tweetEntered.hashtags[i] != NULL){
			free(tweetEntered.hashtags[i]);
			tweetEntered.hashtags[i] = NULL;
		}
	}
	if(tweetEntered.hashtags != NULL){
		free(tweetEntered.hashtags);
		tweetEntered.hashtags = NULL;
	}

	str_index_content = 0;
	str_index_hashtag = 0;
	str_index_tag = 0;

	tweetEntered.content = NULL;
	tweetEntered.hashtags = NULL;
	tweetEntered.tagged_people = NULL;
}

void menu (char *username){

	while (1){
		printf("\n\tMENU:\n (1) Send a Tweet\n (2) View Notifications\n (3) View Wall\n (4) Log Out.\n\n");
		printf("Enter option from menu [1-4]: ");

		int option = 0;
		scanf("%d", &option);

		if (option == 1){
			char *ch = malloc(sizeof(char));

			if (ch == NULL){
					puts("Error - No more memory");
					continue;
			}

			int i = 0;
			puts("\n[SEND A TWEET]\n[EXAMPLE] Hello World! #offlineTwitter @JohnDoe\n");
			printf("Enter a tweet: ");

			ch[i] = getchar(); //reads the newline
			ch[i] = getchar(); //this one actually reads the tweet (first char)

			while (ch[i] != '\n'){
				i++;
				ch = realloc (ch, sizeof(char) * (i + 1));
				if (ch == NULL){
					puts("Error: memory full");
					break;
				}
				ch[i] = getchar();
			}
			ch[i] = '\0';

			if (parseTweet(ch)){
				saveTweet(username);
				puts("Tweet sent!");
			}
			else
			{
				puts("[ERROR] Tweet failed to send.\nEither wrong syntax or user tagged doesn't exist.");
			}

			if (ch != NULL){
				free(ch);
				ch = NULL;
			}

			freeGlobalTweet();

		}
		else if (option == 2){
			puts("[NOTIFICATIONS]\n");
			viewNotifications(username);
		}
		else if(option == 3){
			puts("[WALL]\n");
			viewWall();
		}
		else if (option == 4){
			puts("Successfully logged out.");
			remove(username);
			deleteUsername(username);
			break;
		}
		else {
			puts("Error: option unknown.");
		}
	}
}

int main(int argc, char*argv[]) {

//declaration of some variables
	int usernameExists;
	int i = 0, j = 0;
	char c;

//where everything happens
	if( argc == 2 ) {
    	char *username = argv[1];
    	usernameExists = checkUsername(username);
    	if(usernameExists == 0){
  			puts("Username already exists");
  			return 0;
	  	}

	  	else if (usernameExists == -1){
	  		puts("New account created");

	  		//adding username to users.txt
	  		fusers = fopen("users.txt", "r+");
	  		fseek(fusers, 0, SEEK_END);
	  		c = fgetc(fusers);
				fprintf(fusers, "%s\n", username);
	  		fclose(fusers);

	  		//creating user text file
	  		char *ext = ".txt\0";

	  		while (username[i] != '\0'){
	  			i++;
	  		}
  			while(ext[j] != '\0'){
  				username[i] = ext[j];
  				i++, j++;
  			}
  			username[i] = '\0';
	  		fusers = fopen(username, "w");
	  		fclose(fusers);
	  	}

	  	menu(username);
    }
    else if( argc > 2 ) {
        printf("Too many arguments supplied.\n");
    }
    else {
        printf("Two arguments expected. \n[SYNTAX] ./twitter your_name\n");
    }

  	return 0;
}
