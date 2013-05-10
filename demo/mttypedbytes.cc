#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sstream>
#include "typed_bytes.h"

const std::string kTestStr = "To be, or not to be, that is the question:\n"
                        "Whether 'tis Nobler in the mind to suffer\n"
                        "The Slings and Arrows of outrageous Fortune,\n"
                        "Or to take Arms against a Sea of troubles,\n"
                        "And by opposing end them: to die, to sleep\n"
                        "No more; and by a sleep, to say we end\n"
                        "The Heart-ache, and the thousand Natural shocks\n"
                        "That Flesh is heir to? 'Tis a consummation\n"
                        "Devoutly to be wished. To die to sleep,\n"
                        "To sleep, perchance to Dream; Aye, there's the rub,\n"
                        "For in that sleep of death, what dreams may come,\n"
                        "When we have shuffled off this mortal coil,\n"
                        "Must give us pause. There's the respect\n"
                        "That makes Calamity of so long life:\n"
                        "For who would bear the Whips and Scorns of time,\n"
                        "The Oppressor's wrong, the proud man's Contumely,\n"
                        "The pangs of despised Love, the Law’s delay,\n"
                        "The insolence of Office, and the Spurns\n"
                        "That patient merit of the unworthy takes,\n"
                        "When he himself might his Quietus make\n"
                        "With a bare Bodkin? Who would Fardels bear,\n"
                        "To grunt and sweat under a weary life,\n"
                        "But that the dread of something after death,\n"
                        "The undiscovered Country, from whose bourn\n"
                        "No Traveller returns, Puzzles the will,\n"
                        "And makes us rather bear those ills we have,\n"
                        "Than fly to others that we know not of.\n"
                        "Thus Conscience does make Cowards of us all,\n"
                        "And thus the Native hue of Resolution\n"
                        "Is sicklied o'er, with the pale cast of Thought,\n"
                        "And enterprises of great pitch and moment,\n"
                        "With this regard their Currents turn awry,\n"
                        "And lose the name of Action. Soft you now,\n"
                        "The fair Ophelia? Nymph, in thy Orisons\n"
                        "Be all my sins remembered.";

typedef struct tbarg {
  long num_loops;
} tbarg_t;


void *rwtb(void *targ) {
  tbarg_t *myarg = (tbarg_t *)targ;

  for (long i = 0; i < myarg->num_loops; ++i) {
    strmio::TypedBytes tb;
    std::ostringstream oss;
    tb.set_int_val(123);
    tb.write(oss);
    tb.set_long_val(1234567890);
    tb.write(oss);
    tb.set_string_val(kTestStr);
    tb.write(oss);
    tb.set_bytes_val(kTestStr.c_str(), kTestStr.length());
    tb.write(oss);
    oss.flush();

    std::istringstream iss(oss.str());
    tb.read(iss);
    tb.int_val();
    tb.read(iss);
    tb.long_val();
    tb.read(iss);
    tb.string_val();
    tb.read(iss);
    tb.bytes_val();
  }

  return NULL;
}


int main(int argc, char **argv) {
  long num_loops = LONG_MAX;
  int num_threads = 1;
  int opt;

  while ((opt = getopt(argc, argv, "l:t:")) != -1) {
    switch(opt) {
      case 'l':
        num_loops = atol(optarg);
        break;
      case 't':
        num_threads = atoi(optarg);
        break;
      default:
        std::cerr << "unknown option " << optopt << std::endl;
        exit(1);
    }
  }

  pthread_t threads[num_threads];
  tbarg_t tbargs[num_threads];

  // start threads
  for (int i = 0; i < num_threads; ++i) {
    tbargs[i].num_loops = num_loops;
    pthread_create(&threads[i], NULL, rwtb, (void *)(&tbargs[i]));
  }

  // join threads
  for (int i = 0; i < num_threads; ++i) {
    pthread_join(threads[i], NULL);
  }

  std::cout << "done." << std::endl;
  return 0;
}
