#include "marisa.h"


int input_string(char *str, int max_len) {
  max_len--;
  int ctr = 0;
  str[ctr] = 0;
  while (str[ctr] != '\n') {
    if (Serial.available()) {
        str[ctr] = Serial.read();
        if (str[ctr] >= ' ' && str[ctr] <= '~')
          ctr++;
        if (ctr >= max_len)
          break;
    }
  }
  str[ctr] = 0;
  Serial.println(str);
  return ctr;
}

int input_num() {
  char in[20];
  int ctr = 0;
  in[ctr] = 0;
  while (in[ctr] != '\n') {
    if (Serial.available()) {
        in[ctr] = Serial.read();
        if (in[ctr] >= '0' && in[ctr] <= '9')
            ctr++;
        if (ctr >= sizeof(in))
          break;
    }
  }
  in[ctr] = 0;
  int ret = atoi(in);
  Serial.println(ret);
  return ret;
}

enum {CHOICE_LOOKUP = 1, CHOICE_REV_LOOKUP, CHOICE_COMMON_PFX_SRCH, CHOICE_PREDICTIVE_SRCH};
int askChoice() {
  Serial.println();
  Serial.println(F("Welcome to ESP32 Wrapper for Marisa static dictionary!!"));
  Serial.println(F("-------------------------------------------------------"));
  Serial.println();
  Serial.println(F("1. Lookup"));
  Serial.println(F("2. Reverse Lookup"));
  Serial.println(F("3. Common Prefix search"));
  Serial.println(F("4. Predictive search"));
  Serial.println();
  Serial.print(F("Enter choice: "));
  return input_num();
}

void displayPrompt(const char *title) {
  Serial.print(F("Enter "));
  Serial.println(title);
}

void printElapsed(unsigned long start_time) {
  Serial.println();
  Serial.print("Elapsed time (micro seconds): ");
  Serial.println(micros() - start_time);
}

void printKeyAndId(marisa::Agent& agent) {
  char out_key[100];
  strncpy(out_key, agent.key().ptr(), agent.key().length());
  out_key[agent.key().length()] = '\0';
  Serial.print("Key: ");
  Serial.print(out_key);
  Serial.print(", len: ");
  Serial.print(agent.key().length());
  Serial.print(", id: ");
  Serial.println(agent.key().id());
}

marisa::Trie trie;

void reverse_lookup(int id) {
  marisa::Agent agent;
  agent.set_query(id);
  unsigned long start_time = micros();
  try {
    trie.reverse_lookup(agent);
  } catch (exception ex) {
    Serial.println("Exception thrown: ");
  }
  Serial.println();
  printKeyAndId(agent);
  printElapsed(start_time);
}

void search(const char *key, int choice) {
  marisa::Agent agent;
  agent.set_query(key);
  unsigned long start_time = micros();
  Serial.println();
  while (choice == CHOICE_LOOKUP ? trie.lookup(agent) :
         (choice == CHOICE_COMMON_PFX_SRCH ? trie.common_prefix_search(agent) :
		      trie.predictive_search(agent) )) {
     printKeyAndId(agent);
     if (choice == CHOICE_LOOKUP)
       break;
  }
  printElapsed(start_time);
}

#define KEY_COUNT 487568
void setup() {
  Serial.begin(115200);
  trie.map(data, KEY_COUNT);
}

#define MAX_STR_LEN 500
char str[MAX_STR_LEN];
void loop() {

  int choice = askChoice();
  switch (choice) {
      case CHOICE_LOOKUP:
      case CHOICE_COMMON_PFX_SRCH:
      case CHOICE_PREDICTIVE_SRCH:
        displayPrompt("Enter word or phrase (all lower case): ");
        input_string(str, MAX_STR_LEN);
        if (str[0] == 0) {
          Serial.println("Empty string");
          Serial.println();
        } else
          search(str, choice);
        break;
      case CHOICE_REV_LOOKUP: {
          displayPrompt("Enter id (0 to 487568): ");
          int id = input_num();
          if (id > 0 && id <= KEY_COUNT) {
            reverse_lookup(id);
          } else {
            Serial.println("Empty string");
            Serial.println();
      		}
        }
        break;
      default:
        Serial.println(F("Invalid choice. Try again."));
  }

}