package main.java.li3;

import main.java.common.*;
import main.java.engine.Q4;
import main.java.engine.TCDExample;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import java.io.IOException;
import java.time.LocalDate;
import java.util.List;


public class TesteQ4 {

    public static void main (String[] agrs){

        Dados dados;

        try {

            SAXParserFactory spf = SAXParserFactory.newInstance();
            spf.setNamespaceAware(true);
            SAXParser saxParser = spf.newSAXParser();

            TagsParser handlerTags = new TagsParser(new Dados());
            //saxParser.parse(STDSort.convertToFileURL("../../android/Tags.xml"),  handlerTags);
            saxParser.parse(TCDExample.convertToFileURL("../../ubuntu/Tags.xml"),  handlerTags);

            UsersParser handlerUsers = new UsersParser(handlerTags.getBaseDeDados());
            //saxParser.parse(STDSort.convertToFileURL("../../android/Users.xml"),  handlerUsers);
            saxParser.parse(TCDExample.convertToFileURL("../../ubuntu/Users.xml"),  handlerUsers);

            PostsParser handlerPosts = new PostsParser(handlerUsers.getDados());
            //saxParser.parse(STDSort.convertToFileURL("../../android/Posts.xml"),  handlerPosts);
            saxParser.parse(TCDExample.convertToFileURL("../../ubuntu/Posts.xml"),  handlerPosts);

            dados = handlerPosts.getDados(); // base de dados toda carregada

            List<Long> tmp = null;
            try{
                tmp = Q4.questionsWithTag("nautilus", LocalDate.of(2014,1,1), LocalDate.of(2014,1,31), dados);
            } catch (PostNaoExisteException e){
                System.out.println("Post não existe!");
            }
            System.out.println(tmp);

        } catch (SAXException e){
            System.out.println("Erro: SAXExcpetion");
            e.printStackTrace();
        } catch (IOException e){
            System.out.println("Erro: IOExcpetion");
            e.printStackTrace();
        } catch (ParserConfigurationException e){
            System.out.println("Erro: ParserConfigurationException");
            e.printStackTrace();
        }
    }
}


