package main.java.common;

public class PostExisteException extends Exception{
    /**
     * Construtor vazio.
     */
    public PostExisteException(){
        super();
    }

    /**
     * Construtor parametrizado.
     * @param msg mensagem
     */
    public PostExisteException(String msg){
        super(msg);
    }
}
