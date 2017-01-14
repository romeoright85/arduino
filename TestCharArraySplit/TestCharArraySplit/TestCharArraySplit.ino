



// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
}

// the loop function runs over and over again until power down or reset
void loop() {



char a[] = "name=RRR&school=AAA&roll=111&address=SSS";

char* name = splitCharArray(a, ",");


Serial.println(name);


free(name);


while (1);


}



char* splitCharArray(char* array, char* delimiter)
{

char* tag_list_copy = (char * )malloc(strlen(array) + 1);
char* result = 0;
char* s;

strcpy(tag_list_copy, array);

s = strtok(tag_list_copy, "&");
while (s)
{
char* equals_sign = strchr(s, '=');
if (equals_sign)
{
*equals_sign = 0;
if (0 == strcmp(s, delimiter))
{
equals_sign++;
result = (char *)malloc(strlen(equals_sign) + 1);
strcpy(result, equals_sign);
}
}
s = strtok(0, "&");
}
free(tag_list_copy);

return result;
}


/*



// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
}

// the loop function runs over and over again until power down or reset
void loop() {



		char a[] = "name=RRR&school=AAA&roll=111&address=SSS";

		char* name = getTagValue(a, "name");
		char* school = getTagValue(a, "school");
		char* roll = getTagValue(a, "roll");
		char* address = getTagValue(a, "address");
		char* bad = getTagValue(a, "bad");

		Serial.println(name);
		Serial.println(school);
		Serial.println(roll);
		Serial.println(address);
		Serial.println(bad);

		free(name);
		free(school);
		free(roll);
		free(address);
		free(bad);

		while (1);

	
}



char* getTagValue(char* a_tag_list, char* a_tag)
{

	char* tag_list_copy = (char * )malloc(strlen(a_tag_list) + 1);
	char* result = 0;
	char* s;

	strcpy(tag_list_copy, a_tag_list);

	s = strtok(tag_list_copy, "&");
	while (s)
	{
		char* equals_sign = strchr(s, '=');
		if (equals_sign)
		{
			*equals_sign = 0;
			if (0 == strcmp(s, a_tag))
			{
				equals_sign++;
				result = (char *)malloc(strlen(equals_sign) + 1);
				strcpy(result, equals_sign);
			}
		}
		s = strtok(0, "&");
	}
	free(tag_list_copy);

	return result;
}
*/