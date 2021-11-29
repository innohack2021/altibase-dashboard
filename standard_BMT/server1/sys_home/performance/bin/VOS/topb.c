/* Copyright (c) 1995  Milivoj Davidov (milivoj@fl.net.au) */

/* Beginning of modification history */
/* Written 1995-06-18 by Milivoj Davidov (milivoj@fl.net.au) */
/* End of modification history */

/* top.c */

#pragma  extension_checking   none

/* special prototype to override the too generic one in get_meter_dcls.h */
extern void s$get_processes_meters (char_varying *, char_varying *,
                                    char_varying *, short int *, short int *,
                                    void *, short int *);

#include       <stdio.h>
#include       <stdlib.h>
#include       <string.h>

#include       <get_meter_dcls.h>
#include       <error_codes.h>
#include       <module_info.h>

/* ****************************************************************** */

/* Function prototypes */

static void parse_arg_pid (void);
static void ParseAndInitialise (void);
static void GetInitUsage (void);
static void DisplayTopUsage (void);
static int ExitOnError (char * );
static void ContinueOnError (char * );

extern void s$error(short int *, char_varying *, char_varying *);
extern void s$enable_condition (short int *, void * *, char_varying *, void *);
extern void s$revert_condition (short int *, void * *, char_varying *);
extern void s$parse_command (char_varying *, short int *,
          char_varying *, short int *,       /* iterations */
          char_varying *, short int *,       /* interval */
          char_varying *, char_varying *,    /* pid */
          char_varying *, char_varying *,    /* process */
          char_varying *, char_varying *,    /* user */
          char_varying *, char_varying *,    /* module */
          char_varying *);

extern void s$std_date_time_and_zone (char_varying *, char_varying *, char *);
extern void s$sleep (long int *, short int *);
extern void s$get_module_info(  char_varying (66) *,
                                module_info_v3 *,
                                short int *);

/* ****************************************************************** */

/* Constants */

#define   MAX_PROCESSES       1023  /* Max number of processes */
#define   SEC_TO_SLEEP_UNIT   1024
#define   JIF                 ((double) 65536)
#define   GET_MOD_MET_VER     2
#define   GET_PROC_MET_VER    1

/* ****************************************************************** */

/* General variables */

static short int    max_procs  = MAX_PROCESSES;
static short int    prev_procs = 0;
static short int    curr_procs = 0;

/* ****************************************************************** */

/* Variables for VOS s$ subroutines */

/* Beginning of definitions for s$parse_command() */
char_varying(256)   iterations_desc =
   "option(-n), number, word, min(1), = 1";
short int           arg_iterations;

char_varying(256)   interval_desc =
   "option(-d) number, word, min(1),= 3";
short int           arg_interval;

char_varying(256)   pid_desc =
   "option(-p), string, req";
char_varying(256)   arg_pid;

char_varying(256)   processes_desc =
   "option(-process) string, length(32), secret, = '*'";
char_varying(32)    processes;

char_varying(256)   users_desc =
   "option(-user) user_name, length(65), secret,= '*'";
char_varying(65)    users;

char_varying(256)   module_desc =
   "option(-module) module_name, length(66), secret,= '(current_module)'";
char_varying(66)    module;

char_varying(256)   end_desc_top = "end";

/* End of definitions for s$parse_command() */

static char_varying(32)    curr_date;
static char_varying(32)    curr_time;
static char                curr_zone[3];

static long int            interval;
static long int            init_interval = (2 * SEC_TO_SLEEP_UNIT);
static long int            NUserCpus;

static int pids[20];
static int n_pid = 0;

/* ****************************************************************** */

/* Error definitions */

static char_varying(32)       caller;
static char_varying(256)      error_message;
static short int              error;

/* ****************************************************************** */

/* Get-meters data structures declarations */

typedef struct get_module_meters_template       ModuleMetersInfoT;

typedef struct $shortmap get_processes_meters_template
{
        short int                            version;
        struct processes_meters_array        entry[MAX_PROCESSES];

} ProcessesMetersInfoT;

/* ****************************************************************** */

/* CPU and Memory deltas data structure declaration */

typedef struct
{
     double         delta_cpu;
     long int       delta_mem;
     long int       delta_mem_data;

} DeltaCpuMemT;

/* ****************************************************************** */

/* Data definitions */

static ModuleMetersInfoT      mod_meters1;
static ModuleMetersInfoT      mod_meters2;

static ProcessesMetersInfoT   proc_meters1;
static ProcessesMetersInfoT   proc_meters2;

static ModuleMetersInfoT      * prev_mod_met  = &mod_meters1;
static ModuleMetersInfoT      * curr_mod_met  = &mod_meters2;

static ProcessesMetersInfoT   * prev_proc_met = &proc_meters1;
static ProcessesMetersInfoT   * curr_proc_met = &proc_meters2;

static DeltaCpuMemT           DCpuMem[MAX_PROCESSES];

static  module_info_v3        ModuleInfo; /* s$get_module_info */
static  module_info_v3        * CurModuleInfo = &ModuleInfo;

/* ****************************************************************** */

/* Abbreviations */

#define   PrevModM       prev_mod_met->module_meters
#define   CurrModM       curr_mod_met->module_meters

#define   PrevProcM(Ix)  prev_proc_met->entry[Ix].process_meters
#define   CurrProcM(Ix)  curr_proc_met->entry[Ix].process_meters

#define   PrevProcId(Ix) prev_proc_met->entry[Ix].process_id
#define   CurrProcId(Ix) curr_proc_met->entry[Ix].process_id

/* ****************************************************************** */

/* Code */

static    void      ParseAndInitialise (void)
{
     int ix = 0;

     strcpy (&caller, "top");
     s$parse_command (&caller, &error,
                      &iterations_desc, &arg_iterations,
                      &interval_desc, &arg_interval,
                      &pid_desc, &arg_pid,
                      &processes_desc, &processes,
                      &users_desc, &users,
                      &module_desc, &module,
                      &end_desc_top);
     if (error) { ExitOnError (" "); }

     interval = ((long) arg_interval) * SEC_TO_SLEEP_UNIT;

     parse_arg_pid();

     prev_mod_met->version  = GET_MOD_MET_VER;
     curr_mod_met->version  = GET_MOD_MET_VER;
     prev_proc_met->version = GET_PROC_MET_VER;
     curr_proc_met->version = GET_PROC_MET_VER;
     ModuleInfo.version = MODULE_INFO_VERSION_3;         /* @@@@@@ */

     s$std_date_time_and_zone (&curr_date, &curr_time, curr_zone);

     fflush (stdout);
}

static void parse_arg_pid() {
  char str[256];
  int i;
  char *token = NULL;

  strcpy_nstr_vstr(str, &arg_pid);
  n_pid = 0;

  token = strtok(str, ",");
  while (token != NULL) {
    pids[n_pid] = atoi(token);
    n_pid++;
    token = strtok(NULL, ",");
  }

/*@@
  for (i = 0; i < n_pid; i++) {
    printf("[%d] %d\n", i, pids[i]);
  }
*/
}

static    void      GetInitUsage (void)
{
     s$get_module_meters (&module, prev_mod_met, &error);
     if (error) {
          char  cmod[66];
          strcpy (cmod, &module);
          ExitOnError (cmod);
     }

     s$get_processes_meters (&users, &processes, &module,
                             &max_procs, &prev_procs,
                             prev_proc_met, &error);
     if (error) { ExitOnError ("routine s$get_processes_meters(). "); }

}

static    void      DisplayTopUsage (void)
{
     short int      ix = 0, jx = 0, kx;
     short int match;

     double         LapTime = 0.0;
     ProcessesMetersInfoT     * temp_proc_met = NULL;
     ModuleMetersInfoT        * temp_mod_met  = NULL;

     s$get_module_meters (&module, curr_mod_met, &error);
     if (error) {
          char  cmod[66];
          strcpy (cmod, &module);
          ExitOnError (cmod);
     }

     s$get_processes_meters (&users, &processes, &module,
                             &max_procs, &curr_procs,
                             curr_proc_met, &error);
     if (error) { ExitOnError ("routine s$get_processes_meters(). "); }

     s$get_module_info (&module, CurModuleInfo, &error);
     if (error) { ExitOnError ("routine s$get_module_info(). "); }

     /* @@@ Modify by HKlee */
     NUserCpus = ModuleInfo.n_user_cpus;

     LapTime =
          ((((double) CurrModM.cpu_queue_meters.now.high) +
          (((double) CurrModM.cpu_queue_meters.now.low) / JIF)) -
          (((double) PrevModM.cpu_queue_meters.now.high) +
          (((double) PrevModM.cpu_queue_meters.now.low) / JIF))) *
          ((double) NUserCpus);
     if (LapTime <= (double) 0) { LapTime = (double) arg_interval; }

     for (ix = 0; ix < curr_procs; ix++)
     {
          match = 0;
          for (kx = 0; kx < n_pid; kx++) {
            if (CurrProcId(ix) == pids[kx]) {
              match = 1;
              break;
            }
          }

          if (match != 1) {
            DCpuMem[ix].delta_cpu = 0;
            DCpuMem[ix].delta_mem_data = 0;
            DCpuMem[ix].delta_mem = 0;
            continue;
          }

          DCpuMem[ix].delta_cpu =
               ((double) CurrProcM(ix).
                         cpu_queue_meters.busy_time.high) +
               (((double) CurrProcM(ix).
                         cpu_queue_meters.busy_time.low) / JIF);

          for (jx = 0; jx < prev_procs; jx++)
          {
               if (CurrProcId(ix) == PrevProcId(jx))
               {
                    DCpuMem[ix].delta_cpu  -=
                         ((double) PrevProcM(jx).
                              cpu_queue_meters.busy_time.high) +
                         (((double) PrevProcM(jx).
                              cpu_queue_meters.busy_time.low) / JIF);

                    break;
               }
          }

          DCpuMem[ix].delta_mem_data =
               CurrProcM(ix).unshared_memory_step_meters.pluses -
               CurrProcM(ix).unshared_memory_step_meters.minuses;

          DCpuMem[ix].delta_mem = DCpuMem[ix].delta_mem_data +
               CurrProcM(ix).shared_memory_step_meters.pluses -
               CurrProcM(ix).shared_memory_step_meters.minuses;

     }

     s$std_date_time_and_zone (&curr_date, &curr_time, curr_zone);

     printf(
          "\n"
          "Top CPU/Memory at %v on %v, CPUs:%ld\n"
          "Module Mem - Total:%ld, Wired:%ld, Free:%ld (%.0f%%).\n"
          "      PID  %%CPU    Mem   Code   Data  (User) [Program]\n",
          &curr_time, &module, NUserCpus,
          ModuleInfo.total_phys_pages, ModuleInfo.wired_phys_pages,
          ModuleInfo.free_phys_pages,
          (double) (((ModuleInfo.free_phys_pages) * 100) / ModuleInfo.total_phys_pages));

     for (ix = 0; ix < curr_procs; ix++)
     {
          match = 0;
          for (kx = 0; kx < n_pid; kx++) {
            if (CurrProcId(ix) == pids[kx]) {
              match = 1;
              break;
            }
          }

          if (match != 1) continue;

          printf("%9ld %5.2f %6ld %6ld %6ld  (%v) [%v]\n",
               CurrProcId(ix),
               (DCpuMem[ix].delta_cpu * 100.0) / LapTime,
               DCpuMem[ix].delta_mem,
               DCpuMem[ix].delta_mem -
                    DCpuMem[ix].delta_mem_data,
               DCpuMem[ix].delta_mem_data,
               &CurrProcM(ix).user_name,
               &CurrProcM(ix).program_name);
     }

     fflush (stdout);


     prev_procs = curr_procs;

     /* Do not use memcpy(), swapping pointers is MUCH faster.
     */
     temp_proc_met = prev_proc_met;
     prev_proc_met = curr_proc_met;
     curr_proc_met = temp_proc_met;

     temp_mod_met = prev_mod_met;
     prev_mod_met = curr_mod_met;
     curr_mod_met = temp_mod_met;
}

static int ExitOnError (char * Text)
{
     short int CErr = 0;

     strcpy (&error_message, Text);
     s$error (&error, &caller, &error_message);
     exit (error);
}

static void ContinueOnError (char * Text)
{
     strcpy (&error_message, Text);
     s$error (&error, &caller, &error_message);
}

int main ()
{
     int sleep_interval;

     ParseAndInitialise ();

     GetInitUsage ();
     sleep_interval = init_interval;

     while (arg_iterations) {
          s$sleep (&sleep_interval, &error);
          if (error) { ExitOnError ("routine s$sleep(). "); }

          DisplayTopUsage ();
          sleep_interval = interval;
          arg_iterations--;
     }

     return 0;
}

/* end top.c */

