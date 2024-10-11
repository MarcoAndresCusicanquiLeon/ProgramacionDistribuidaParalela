using CalculosMatematicos;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Calculadora
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("---Calculadora con notación Prefija (Notación Polaca)---\n");

            Console.WriteLine("------Ejemplo:------");
            string expr = "+ 3 * 2,4 4,5";
            Console.WriteLine(expr);
            Console.WriteLine("da como resultado "+Operaciones.solve(expr)+"\n");

            Console.WriteLine("Ingresa una expresion:");
            expr=Console.ReadLine();
            Console.WriteLine("Resultado: "+Operaciones.solve(expr));
            Console.ReadLine();
        }
    }
}
