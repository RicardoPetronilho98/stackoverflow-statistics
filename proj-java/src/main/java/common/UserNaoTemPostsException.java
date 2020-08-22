package main.java.common;

public class UserNaoTemPostsException extends Exception{

    /**
     * Construtor vazio.
     */
    public UserNaoTemPostsException(){
        super();
    }

    /**
     * Construtor parametrizado.
     * @param msg mensagem
     */
    public UserNaoTemPostsException(String msg){
        super(msg);
    }
}
