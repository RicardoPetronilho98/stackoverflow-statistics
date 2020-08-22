package main.java.common;

public class PostNaoExisteException extends Exception {
    /**
     * Construtor vazio.
     */
    public PostNaoExisteException(){
        super();
    }

    /**
     * Construtor parametrizado.
     * @param msg mensagem
     */
    public PostNaoExisteException(String msg){
        super(msg);
    }
}
