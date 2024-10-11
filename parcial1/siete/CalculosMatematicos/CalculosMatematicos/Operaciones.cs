using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;

namespace CalculosMatematicos
{
    public class Operaciones
    {
        public static double add(double a, double b)
        {
            return a + b;
        }
        public static double sub(double a, double b)
        {
            return a - b;
        }
        public static double mul(double a, double b)
        {
            return a * b;
        }
        public static double div(double a, double b)
        {
            return a / b;
        }

        public static double solve(string expr)
        {
            string[] decomposition=expr.Split();
            Array.Reverse(decomposition);

            Stack<double> nums_helper=new Stack<double>();
            foreach (string piece in decomposition)
            {
                if (double.TryParse(piece, out double number))
                {
                    nums_helper.Push(number);
                }
                else
                {
                    if (nums_helper.Count < 2)
                    {
                        throw new InvalidOperationException("Se requieren al menos dos operandos para realizar la operación.");
                    }
                    double topnum1 = nums_helper.Pop();
                    double topnum2 = nums_helper.Pop();

                    double result;
                    switch (piece)
                    {
                        case "+":
                            result=add(topnum1, topnum2);
                            break;
                        case "-":
                            result=sub(topnum1, topnum2);
                            break;
                        case "*":
                            result = mul(topnum1, topnum2);
                            break;
                        case "/":
                            result = div(topnum1, topnum2);
                            break;
                        default:
                            throw new InvalidOperationException("Operador no válido");
                    };

                    nums_helper.Push(result);
                }
            }
            if (nums_helper.Count > 1) throw new InvalidOperationException("Cantidad de números incorrecta");
            return nums_helper.Pop();
        }
    }
}
