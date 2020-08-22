package main.java.common;

public class UserExisteException extends Exception{
    /**
     * Construtor vazio.
     */
    public UserExisteException(){
        super();
    }

    /**
     * Construtor parametrizado.
     * @param msg mensagem
     */
    public UserExisteException(String msg){
        super(msg);
    }
}
