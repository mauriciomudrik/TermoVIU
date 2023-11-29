using System;

namespace TermoVIUservice 
{
    public class TVservice {
        
        public string processCall(string inCommand) {
            // Retorna os comandos da interface
            if(inCommand.Contains("list")) {
                return("list has received");
            }
            
            // List all temperature readings
            if(inCommand.Contains("read")) {
                return("read has received");
            }
            return(null);
            
        }



    }
}