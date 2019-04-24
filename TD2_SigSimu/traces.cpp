#include <systemc.h>
#include <string> 
int sc_main (int argc, char * argv[])
{
   // Un pointeur sur l'objet qui permet de gérer les traces
   sc_trace_file *trace_f;

   // Cette fonction crée l'objet
   // L'argument est le nom du fichier qui sera créé.
   // L'extension .vcd est ajoutée automatiquement
   trace_f = sc_create_vcd_trace_file ("my_simu_trace");
   // On peut aussi préciser l'unité de temps dans le fichier vcd
   trace_f->set_time_unit(1,SC_NS);

   int t = 0;

   // Ajoute la variable t aux éléments à tracer
   // Les arguments de la fonction sont:
   //    - le pointeur vers le fichier de trace
   //    - la variable/objet à tracer
   //    - le nom dans dans le fichier généré
   sc_trace(trace_f, t, "t");

    if (argc != 2){
        printf("Number of arguments should be 2; EXIT!\n");
        return 1;
        }
   // La simulation
   int N = std::stoi(argv[1]);
   if (N < 0 || N > 255){
        printf("N should be positive and less or equal than 255\n");
        return 2;
        }
   for (int i=0 ; i<= N;i++){
       sc_start(10,SC_NS);
        t++; 
   }
   
   // Ferme le fichier de trace
   // ne peut êter fait qu'à la fin de la simulation
   sc_close_vcd_trace_file(trace_f);

   return 0;
}