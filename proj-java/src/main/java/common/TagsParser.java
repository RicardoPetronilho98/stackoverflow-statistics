package main.java.common;

import org.xml.sax.Attributes;
import org.xml.sax.helpers.DefaultHandler;


public class TagsParser extends DefaultHandler {

    private Dados baseDeDados;

    public TagsParser(Dados dados){
        super();
        this.baseDeDados = dados.clone();
    }

    public Dados getBaseDeDados(){
        return this.baseDeDados.clone();
    }

    /**
     * Método que é executado no fim do parser.
     */
    public void endDocument(){
        System.out.println("\nTags Parser done!\n");
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

            String tagName = atts.getValue("TagName");
            Long id = Long.parseLong( atts.getValue("Id") );

            try {
                Tag tag = new Tag(id, tagName);
                this.baseDeDados.add(tag);

            }  catch (TagExisteException e){
                System.out.println("Erro: Tag a adicionar já existe. Tag não foi adiconada!" );
                e.printStackTrace();
            } catch (ValoresInvalidosException e){
                System.out.println("Erro: criação da Tag com id - " + Long.toString(id) + " - tem parâmetros inváidos. Tag não foi adicionada!");
                e.printStackTrace();
            }
        }
    }

}
