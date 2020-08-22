package main.java.li3;

import main.java.common.Dados;
import main.java.common.PostsParser;
import main.java.common.TagsParser;
import main.java.common.UsersParser;
import main.java.engine.Q7;
import main.java.engine.TCDExample;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import java.io.IOException;
import java.time.LocalDate;
import java.util.List;

public class TesteQ7 {
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
            LocalDate begin = LocalDate.of(2014,8,1);
            LocalDate end = LocalDate.of(2014,8,11);
            System.out.println(System.currentTimeMillis());
            List<Long> list = Q7.mostAnsweredQuestions(dados,10,begin,end);
            System.out.println(System.currentTimeMillis());
            System.out.println(list);
            System.out.println(list.contains((long)505506));
            System.out.println(list.contains((long)508221));
            System.out.println(list.contains((long)506510));
            System.out.println(list.contains((long)508029));
            System.out.println(list.contains((long)506824));
            System.out.println(list.contains((long)505581));
            System.out.println(list.contains((long)505368));
            System.out.println(list.contains((long)509498));
            System.out.println(list.contains((long)509283));
            System.out.println(list.contains((long)508635));


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
