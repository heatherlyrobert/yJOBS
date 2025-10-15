

char       /*----: set up program urgents/debugging --------------------------*/
yjobs__unit_quiet       (void)
{
   yURG_err_none ();
   yURG_msg_none ();
   yjobs_runas ("khronos", NULL);
   yJOBS_rmdirs ();
   yjobs_yscore_init ();
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
yjobs__unit_loud        (void)
{
   int         x_narg       = 4;
   char       *x_args [ 4]  = {"yJOBS_unit" , "@@kitchen", "@@yjobs", "@@yenv"};
   yURG_logger   (x_narg, x_args);
   yURG_urgs     (x_narg, x_args);
   /*> yLOGS_begin   ("yJOBS_unit", YLOG_SYS, YLOG_NOISE);                            <*/
   /*> yURG_by_name  ("yjobs", YURG_ON);                                              <*/
   yURG_err_none ();
   yURG_msg_none ();
   yjobs_runas ("khronos", NULL);
   yJOBS_rmdirs ();
   DEBUG_YJOBS  yLOG_info     ("yJOBS"     , yJOBS_version   ());
   yjobs_yscore_init ();
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
yjobs__unit_end         (void)
{
   yjobs_runas ("", NULL);
   yJOBS_wrap    ();
   yLOGS_end     ();
   return 0;
}
