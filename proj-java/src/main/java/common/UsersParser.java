package main.java.common;

import org.xml.sax.Attributes;
import org.xml.sax.helpers.DefaultHandler;

import java.util.ArrayList;

public class UsersParser extends DefaultHandler {

    private Dados dados;

    public UsersParser(Dados dados){
        super();
        this.dados = dados.clone();
    }

    public Dados getDados(){
        return this.dados.clone();
    }

    /**
     * Método que é executado no fim do parser.
     */
    public void endDocument(){
        System.out.println("\nUsers Parser done!\n");
    }

    /**
     * Método que é executado no início de cada elemento.
     *
     * @param namespaceURI
     * @param localName
     * @param qName nome do elemento
     * @param atts
     */
    public void startElement(String namespaceURI, String localName, String qName, Attributes atts){

        if (qName.equals("row")) {

            long id = Long.parseLong( atts.getValue("Id") );
            int reputacao  = Integer.parseInt( atts.getValue("Reputation") );
            String nome = atts.getValue("DisplayName");

            String bio = atts.getValue("AboutMe");
            if (bio == null) bio = "";

            int upVotes = Integer.parseInt( atts.getValue("UpVotes") );
            int downVotes = Integer.parseInt( atts.getValue("DownVotes") );

            try {
                User user = new User(id, reputacao, nome, bio, new ArrayList<>(), upVotes, downVotes, 0);
                this.dados.add(user);

            } catch (UserExisteException e){
                System.out.println("Erro: User a adicionar já existe. User não foi adiconado!" );
                e.printStackTrace();
            } catch (ValoresInvalidosException e){
                System.out.println("Erro: criação do User com id - " + Long.toString(id) + " - tem parâmetros inváidos. User não foi adicionado!");
                e.printStackTrace();
            }
        }
    }
}
