using Antlr.Runtime;
using AntlrTest;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace generator
{
    class Program
    {
        static void Main(string[] args)
        {
            const string input = "1+4/2";
            var lex = new SimpleCalcLexer(new ANTLRStringStream(input));
            var tokens = new CommonTokenStream(lex);
            var parser = new SimpleCalcParser(tokens);

            var ret = parser.expr();
        }
    }
}
