public class Gerenciador {  
 
 public static void main(String args[]) {  
    
    // Cria um Objeto de Pessoa.  
    Pessoa pVitor;  
    pVitor = new Pessoa("Vitor Fernando Pamplona", 25 );   
      
    // Vitor Recebeu 1000 reais  
    // Inclui R$ 1000 na carteira da   
    // pessoa p criada na linha anterior  
    pVitor.receber(1000);   
      
    // Cria um outro objeto de pessoa, o Joao  
    Pessoa pJoao = new Pessoa("João da Silva", 10);   
      
    // João recebeu R$ 500 e gastou R$ 100  
     pJoao.receber(500);  
     pJoao.gastar(100);  


    // Mostra quanto cada um ficou

    System.out.print(pVitor.nome);
    System.out.print(", ");
    System.out.print(pVitor.idade);
    System.out.print(" anos, tem R$ ");
    System.out.println(pVitor.dinheiroNaCarteira);
    System.out.print(pJoao.nome);
    System.out.print(", ");
    System.out.print(pJoao.idade);
    System.out.print(" anos, tem R$ ");
    System.out.println(pJoao.dinheiroNaCarteira);
  }  
}  
