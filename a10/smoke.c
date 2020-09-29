#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#include "uthread.h"
#include "uthread_mutex_cond.h"

#define NUM_ITERATIONS 1000

#ifdef VERBOSE
#define VERBOSE_PRINT(S, ...) printf (S, ##__VA_ARGS__)
#else
#define VERBOSE_PRINT(S, ...) ((void) 0) // do nothing
#endif
//ct
struct Agent {
  uthread_mutex_t mutex;
  uthread_cond_t  match;
  uthread_cond_t  paper;
  uthread_cond_t  tobacco;
  uthread_cond_t  smoke;
};

struct Agent* createAgent() {
  struct Agent* agent = malloc (sizeof (struct Agent));
  agent->mutex   = uthread_mutex_create();
  agent->paper   = uthread_cond_create(agent->mutex);
  agent->match   = uthread_cond_create(agent->mutex);
  agent->tobacco = uthread_cond_create(agent->mutex);
  agent->smoke   = uthread_cond_create(agent->mutex);
  return agent;
}

//
// TODO
// You will probably need to add some procedures and struct etc.
//

struct init {
  struct Agent *agent;
  int paper;
  int tobacco;
  int match;
  uthread_cond_t paper_tobacco;
  uthread_cond_t paper_match;
  uthread_cond_t match_tobacco;
  uthread_cond_t smoke;

};

struct init* createInit (struct Agent* agent) {
  struct init* i = malloc(sizeof(struct init));
  i->agent = agent;
  i->paper = 0;
  i->tobacco = 0;
  i-> match = 0;
  i->paper_tobacco = uthread_cond_create(agent->mutex);
  i->paper_match = uthread_cond_create(agent->mutex);
  i->match_tobacco = uthread_cond_create(agent->mutex);
  i->smoke = uthread_cond_create(agent->mutex);
  return i;
}

/**
 * You might find these declarations helpful.
 *   Note that Resource enum had values 1, 2 and 4 so you can combine resources;
 *   e.g., having a MATCH and PAPER is the value MATCH | PAPER == 1 | 2 == 3
 */
enum Resource            {    MATCH = 1, PAPER = 2,   TOBACCO = 4};
char* resource_name [] = {"", "match",   "paper", "", "tobacco"};

// # of threads waiting for a signal. Used to ensure that the agent
// only signals once all other threads are ready.
int num_active_threads = 0;

int signal_count [5];  // # of times resource signalled
int smoke_count  [5];  // # of times smoker with resource smoked

/**
 * This is the agent procedure.  It is complete and you shouldn't change it in
 * any material way.  You can modify it if you like, but be sure that all it does
 * is choose 2 random resources, signal their condition variables, and then wait
 * wait for a smoker to smoke.
 */
void* agent (void* av) {
  struct Agent* a = av;
  static const int choices[]         = {MATCH|PAPER, MATCH|TOBACCO, PAPER|TOBACCO};
  static const int matching_smoker[] = {TOBACCO,     PAPER,         MATCH};

  srandom(time(NULL));
  
  uthread_mutex_lock (a->mutex);
  // Wait until all other threads are waiting for a signal
  while (num_active_threads < 3)
    uthread_cond_wait (a->smoke);

  for (int i = 0; i < NUM_ITERATIONS; i++) {
    int r = random() % 6;
    switch(r) {
    case 0:
      signal_count[TOBACCO]++;
      VERBOSE_PRINT ("match available\n");
      uthread_cond_signal (a->match);
      VERBOSE_PRINT ("paper available\n");
      uthread_cond_signal (a->paper);
      break;
    case 1:
      signal_count[PAPER]++;
      VERBOSE_PRINT ("match available\n");
      uthread_cond_signal (a->match);
      VERBOSE_PRINT ("tobacco available\n");
      uthread_cond_signal (a->tobacco);
      break;
    case 2:
      signal_count[MATCH]++;
      VERBOSE_PRINT ("paper available\n");
      uthread_cond_signal (a->paper);
      VERBOSE_PRINT ("tobacco available\n");
      uthread_cond_signal (a->tobacco);
      break;
    case 3:
      signal_count[TOBACCO]++;
      VERBOSE_PRINT ("paper available\n");
      uthread_cond_signal (a->paper);
      VERBOSE_PRINT ("match available\n");
      uthread_cond_signal (a->match);
      break;
    case 4:
      signal_count[PAPER]++;
      VERBOSE_PRINT ("tobacco available\n");
      uthread_cond_signal (a->tobacco);
      VERBOSE_PRINT ("match available\n");
      uthread_cond_signal (a->match);
      break;
    case 5:
      signal_count[MATCH]++;
      VERBOSE_PRINT ("tobacco available\n");
      uthread_cond_signal (a->tobacco);
      VERBOSE_PRINT ("paper available\n");
      uthread_cond_signal (a->paper);
      break;
    }
    VERBOSE_PRINT ("agent is waiting for smoker to smoke\n");
    uthread_cond_wait (a->smoke);
  }
  
  uthread_mutex_unlock (a->mutex);
  return NULL;
}

void* paper_posessor (void* iv) {
  struct init* i = iv;
  uthread_mutex_lock(i->agent->mutex);
  while(1) {
        VERBOSE_PRINT ("%s possesor is waiting\n", resource_name [2]);
    uthread_cond_wait(i->match_tobacco);
    VERBOSE_PRINT ("%s possesor is smoking\n", resource_name [2]);
    i->paper = 0;
    i->tobacco = 0;
    i->match = 0;
    smoke_count[2]++;
    uthread_cond_signal(i->agent->smoke);
  }
  uthread_mutex_unlock(i->agent->mutex);
  return NULL;
}

void* tobacco_posessor (void* iv) {
  struct init* i = iv;
  uthread_mutex_lock(i->agent->mutex);
  while(1) {
    VERBOSE_PRINT ("%s possesor is waiting\n", resource_name [4]);
    uthread_cond_wait(i->paper_match);
    VERBOSE_PRINT ("%s posessor is smoking\n", resource_name [4]);
    i->paper = 0;
    i->tobacco = 0;
    i->match = 0;
    smoke_count[4]++;
    uthread_cond_signal(i->agent->smoke);
  }
  uthread_mutex_unlock(i->agent->mutex);
  return NULL;
}

void* match_posessor (void* iv) {
  struct init* i = iv;
  uthread_mutex_lock(i->agent->mutex);
  while(1) {
    VERBOSE_PRINT ("%s possesor is waiting\n", resource_name [1]);
    uthread_cond_wait(i->paper_tobacco);
    VERBOSE_PRINT ("%s possesor is smoking\n", resource_name [1]);
    i->paper = 0;
    i->tobacco = 0;
    i->match = 0;
    smoke_count[1]++;
    uthread_cond_signal(i->agent->smoke);
  }
  uthread_mutex_unlock(i->agent->mutex);
  return NULL;
}

void* matchInit (void* pv) {
    struct init* p = pv;
    uthread_mutex_lock (p->agent->mutex);
    while (1) {
      VERBOSE_PRINT ("waiting for %s\n", resource_name [1]);
      uthread_cond_wait (p->agent->match);
      VERBOSE_PRINT ("currently posess %s\n", resource_name [1]);
      p->match = 1;
      if (p->match + p->paper + p->tobacco == 2) {
        if (p->paper == 0){
          uthread_cond_signal (p->match_tobacco);
        }
        if (p->tobacco == 0){
          uthread_cond_signal (p->paper_match);
        }  
      }
    }
  uthread_mutex_unlock (p->agent->mutex);
  return NULL;
}


void* paperInit (void* pv) {
  struct init* p = pv;
    uthread_mutex_lock (p->agent->mutex);
    while (1) {
      VERBOSE_PRINT ("waiting for %s\n", resource_name [2]);
      uthread_cond_wait (p->agent->paper);
      VERBOSE_PRINT ("currently posess %s\n", resource_name [2]);
      p->paper = 1;
      if (p->match + p->paper + p->tobacco == 2) {
        if (p->match == 0) {
          uthread_cond_signal (p->paper_tobacco);
        }
        if (p->tobacco == 0){
          uthread_cond_signal (p->paper_match);
        }  
      }
    
  }
  uthread_mutex_unlock (p->agent->mutex);
  return NULL;
}

void* tobaccoInit (void* pv) {
    struct init* p = pv;
    uthread_mutex_lock (p->agent->mutex);
    while (1) {
      VERBOSE_PRINT ("waiting for %s\n", resource_name [4]);
      uthread_cond_wait (p->agent->tobacco);
      VERBOSE_PRINT ("currently posess %s\n", resource_name [4]);
      p->tobacco = 1;
      if (p->match + p->paper + p->tobacco == 2) {
        if (p->match == 0) {
          uthread_cond_signal (p->paper_tobacco);
        }
        if (p->paper == 0){
          uthread_cond_signal (p->match_tobacco);
        }
        
    }
    }
  uthread_mutex_unlock (p->agent->mutex);
  return NULL;
}

int main (int argc, char** argv) {
  
  struct Agent* a = createAgent();
  uthread_t agent_thread;

  uthread_init(5);
  struct init* i = createInit (a);
  
  uthread_create (paperInit,i);
  uthread_create (tobaccoInit,i);
  uthread_create (matchInit,i);
  uthread_create (paper_posessor,i);
  num_active_threads++;
  uthread_create (tobacco_posessor,i);
  num_active_threads++;
  uthread_create (match_posessor,i);
  num_active_threads++;
  agent_thread = uthread_create(agent, a);
  uthread_join(agent_thread, NULL);

  assert (signal_count [MATCH]   == smoke_count [MATCH]);
  assert (signal_count [PAPER]   == smoke_count [PAPER]);
  assert (signal_count [TOBACCO] == smoke_count [TOBACCO]);
  assert (smoke_count [MATCH] + smoke_count [PAPER] + smoke_count [TOBACCO] == NUM_ITERATIONS);

  printf ("Smoke counts: %d matches, %d paper, %d tobacco\n",
          smoke_count [MATCH], smoke_count [PAPER], smoke_count [TOBACCO]);

  return 0;
}
 