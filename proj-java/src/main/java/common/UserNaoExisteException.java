package main.java.common;

public class UserNaoExisteException extends Exception {
    /**
     * Construtor vazio.
     */
    public UserNaoExisteException(){
        super();
    }

    /**
     * Construtor parametrizado.
     * @param msg mensagem
     */
    public UserNaoExisteException(String msg){
        super(msg);
    }
}
