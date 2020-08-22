package main.java.common;

import java.time.LocalDate;

import org.xml.sax.Attributes;
import org.xml.sax.helpers.DefaultHandler;


public class PostsParser extends DefaultHandler  {
    private Dados dados;

    public PostsParser(Dados dados){
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
        System.out.println("\nPosts Parser done!\n");
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
            int tipo = Integer.parseInt(atts.getValue("PostTypeId"));
            long userId = Long.parseLong(atts.getValue("OwnerUserId"));
            this.dados.add(userId, id, tipo); // adiciona o id do post ao user
            String strData = atts.getValue("CreationDate");
            LocalDate data = LocalDate.parse( strData.substring(0, 10) );
            int score = Integer.parseInt(atts.getValue("Score"));
            int commentCount = Integer.parseInt(atts.getValue("CommentCount"));

            String titulo = atts.getValue("Title");
            if (titulo == null) titulo = "";

            String tags = atts.getValue("Tags");
            if (tags == null) tags = "";

            long answerCount = 0;
            String answerCountStr = atts.getValue("AnswerCount");
            if (answerCountStr != null) answerCount = Long.parseLong(answerCountStr);

            long parentId = 0;
            String parentIdStr = atts.getValue("ParentId");
            if (parentIdStr != null) parentId = Long.parseLong(parentIdStr);

            try {
                Post post = new Post( id, tipo, userId, parentId, titulo, tags, data, answerCount, score, commentCount,0,0);
                this.dados.add(post);

            } catch (PostExisteException e) {
                System.out.println("Erro: Post a adicionar já existe. Post não foi adiconado!" );
                e.printStackTrace();
            } catch (ValoresInvalidosException e){
                System.out.println("Erro: criação do Post com id - " + Long.toString(id) + " - tem parâmetros inváidos. Post não foi adicionado!");
                e.printStackTrace();
            }
        }
    }
}
