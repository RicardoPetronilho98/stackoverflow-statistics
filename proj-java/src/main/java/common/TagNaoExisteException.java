package main.java.common;

public class TagNaoExisteException extends Exception{
    /**
     * Construtor vazio.
     */
    public TagNaoExisteException(){
        super();
    }

    /**
     * Construtor parametrizado.
     * @param msg mensagem
     */
    public TagNaoExisteException(String msg){
        super(msg);
    }
}
