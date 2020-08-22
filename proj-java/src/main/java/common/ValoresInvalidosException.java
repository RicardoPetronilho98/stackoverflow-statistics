package main.java.common;

public class ValoresInvalidosException extends Exception{

    /**
     * Construtor vazio.
     */
    public ValoresInvalidosException(){
        super();
    }

    /**
     * Construtor parametrizado.
     *
     * @param msg mensagem informativa da exepcao ocurrida
     */
    public ValoresInvalidosException(String msg){
        super(msg);
    }
}
