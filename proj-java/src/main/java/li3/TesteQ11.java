package main.java.li3;

import main.java.common.*;
import main.java.engine.Q11;
import main.java.engine.TCDExample;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import java.io.IOException;
import java.time.LocalDate;
import java.util.List;

public class TesteQ11 {
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
            LocalDate begin = LocalDate.of(2014,1,1);
            LocalDate end = LocalDate.of(2014,12,31);
            try{
                System.out.println(System.currentTimeMillis());
                List<Long> list = Q11.mostUsedBestRep(dados,10,begin,end);
                System.out.println(System.currentTimeMillis());
                System.out.println(list);
                System.out.println(list.contains((long)5629));
                System.out.println(list.contains((long)103));
                System.out.println(list.contains((long)277));
                System.out.println(list.contains((long)431));
                System.out.println(list.contains((long)9));
                System.out.println(list.contains((long)133));
                System.out.println(list.contains((long)140));
                System.out.println(list.contains((long)72));
                System.out.println(list.contains((long)80));
                System.out.println(list.contains((long)201));
            } catch (TagNaoExisteException e){
                System.out.println("Erro: Tag não existe");
                e.printStackTrace();
            } catch (PostNaoExisteException e){
                System.out.println("Erro: Post id não existe");
                e.printStackTrace();
            }

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
