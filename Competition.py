# -*- coding: utf-8 -*-

from time import sleep
import pymysql.cursors

# Connect to the database
connection = pymysql.connect(host='115.159.39.220',
                             user='root',
                             password='mooc-all',
                             db='Moocs',
                             charset='utf8mb4',
                             cursorclass=pymysql.cursors.DictCursor)

def Add_user (names):

    try:
        with connection.cursor() as cursor:
            Add_sql = """INSERT INTO ACMer(name)
                           values("%s");"""
            for item in names :
                cmd = (Add_sql % (item));
                try:
                    print(cmd)
                    cursor.execute(cmd)
                    connection.commit()
                except:
                        connection.rollback()

    finally:
        connection.close()


def Add_competition(rank):
    try:
        with connection.cursor() as cursor:
            sql = """select * from ACMer"""
            cursor.execute(sql)
            res = cursor.fetchall()
            n_res = {}
            for item in res:
                n_res[item['name']] = item;
            for winner in range(len(rank)):
                winner = len(rank) - 1 - winner;
                n_res[rank[winner]]['times'] = n_res[rank[winner]]['times'] + 1;
                for losser in range(winner + 1, len(rank)):
                    if(n_res[rank[winner]]['credits'] < n_res[rank[losser]]['credits'] + 5) :
                        n_res[rank[winner]]['credits'] = n_res[rank[losser]]['credits'] + 5
                        n_res[rank[winner]]['enemy'] = n_res[rank[losser]]['name']



            update_sql = """UPDATE ACMer SET times = %s, credits = %s, enemy = '%s' 
                            WHERE name = '%s' """

            for item in rank:
                upup = n_res[item];
                cmd = (update_sql % (upup['times'], upup['credits'], upup['enemy'], upup['name']));
                try:
                    print(cmd)
                    cursor.execute(cmd)
                    connection.commit()
                except:
                    connection.rollback()


    finally:
        connection.close()


# Add_user(["王超毅", ""])
#"罗龙君", "唐胜洋", "顾家祺"
Add_competition(["唐胜洋", "罗龙君", "顾家祺"])
















