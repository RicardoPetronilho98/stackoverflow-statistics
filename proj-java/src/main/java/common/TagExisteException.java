package main.java.common;

public class TagExisteException extends Exception{
    /**
     * Construtor vazio.
     */
    public TagExisteException(){
        super();
    }

    /**
     * Construtor parametrizado.
     * @param msg mensagem
     */
    public TagExisteException(String msg){
        super(msg);
    }
}
