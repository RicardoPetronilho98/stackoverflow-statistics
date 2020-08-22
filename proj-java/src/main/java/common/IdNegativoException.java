package main.java.common;

public class IdNegativoException extends Exception  {
    /**
     * Construtor vazio.
     */
    public IdNegativoException(){
        super();
    }

    /**
     * Construtor parametrizado.
     * @param msg mensagem
     */
    public IdNegativoException(String msg){
        super(msg);
    }
}
