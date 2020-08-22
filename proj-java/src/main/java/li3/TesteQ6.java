package main.java.li3;

import main.java.common.*;
import main.java.engine.Q6;
import main.java.engine.TCDExample;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import java.io.IOException;
import java.time.LocalDate;
import java.util.List;

public class TesteQ6 {
    public static void main (String[] agrs){

        Dados dados;

        try {

            SAXParserFactory spf = SAXParserFactory.newInstance();
            spf.setNamespaceAware(true);
            SAXParser saxParser = spf.newSAXParser();

            TagsParser handlerTags = new TagsParser(new Dados());
            //saxParser.parse(TCDExample.convertToFileURL("../../android/Tags.xml"),  handlerTags);
            saxParser.parse(TCDExample.convertToFileURL("../../ubuntu/Tags.xml"),  handlerTags);

            UsersParser handlerUsers = new UsersParser(handlerTags.getBaseDeDados());
            //saxParser.parse(TCDExample.convertToFileURL("../../android/Users.xml"),  handlerUsers);
            saxParser.parse(TCDExample.convertToFileURL("../../ubuntu/Users.xml"),  handlerUsers);

            PostsParser handlerPosts = new PostsParser(handlerUsers.getDados());
            //saxParser.parse(TCDExample.convertToFileURL("../../android/Posts.xml"),  handlerPosts);
            saxParser.parse(TCDExample.convertToFileURL("../../ubuntu/Posts.xml"),  handlerPosts);

            dados = handlerPosts.getDados(); // base de dados toda carregada

            //dados.writeOnFile("dados.txt");
            LocalDate begin = LocalDate.of(2015,11,1);
            LocalDate end = LocalDate.of(2015,11,30);

            List<Long> list = Q6.mostVotedAnswers(dados,5,begin,end);
            System.out.println(list); // 701775;697197;694560;696641;704208;
            System.out.println(list.contains((long)701775));
            System.out.println(list.contains((long)697197));
            System.out.println(list.contains((long)694560));
            System.out.println(list.contains((long)696641));
            System.out.println(list.contains((long)704208));

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
