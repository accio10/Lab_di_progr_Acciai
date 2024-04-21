ACCIAI NATHAN

Laboratorio di programmazione

Docente: Marco Bertini


Acciai Nathan





Realizzazione di un applicazione bancaria che consente a un utente di eseguire le operazioni base sul proprio conto e sul conto delle persone che ha in rubrica, consente anche la visualizzazione di esse e salva anche il report delle azioni eseguite su un file di testo


 
In questo progetto è stata creata un’ applicazione bancaria che gestisce le operazione di un utente, sia che esse siano rivolte al proprio conto corrente, sia che queste vengano effettuate sul conto di utenti esterni
Il progetto a tre classi principali:
1.	Transaction: È la classe che crea l’oggetto transazione e ne specifica la data in cui viene stata effettuata, il tipo di transazione se è un flusso uscente o entrante, il mittente che effettivamente esegue quella transazione e infine la causa della transazione che può essere:
a.	Prelievo: se l’utente preleva dal proprio conto
b.	Versamento: se l’utente versa nel proprio conto
c.	Pagamento: se l’utente effettua un pagamento sul conto di un altro utente
d.	Test: definito per la parte di UnitTest
Questa classe effettivamente va a creare una transazione che può essere creata con lo svincolo della data e di default è il sistema a assegnare la data odierna e l’ora in cui viene creata la transazione,per poi poterla andare a modificare successivamente se occorre; oppure la transazione può essere creata anche andando a inserire la data in cui essa è stata o sarà eseguita
2.	Account: È la classe che crea un account per l’utente e tiene in memoria tutte le transazioni da esso effettuate, contiene anche i massimali raggiungibili da una transazione a livello monetario, e il saldo iniziale ovviamente inizializzato a 0
Questa classe si occupa di creare, inserire e cancellare transazioni, essa si basa su un vettore di unique_ptr della classe Transaction essendo che la transazione deve essere unica quando viene creata o inserita 
Questa classe si occupa inoltre di andare a scrivere il report dell’Utente sul proprio file di testo quando vengono fatte le opportune operazioni sulle transazioni 
Infine essa si occupa anche di andare a ricercare dentro il vettore le transazioni sia tutte le transazioni sia transazioni per ricerca basata su data oppure per la tipologia della transazione cercata
User: È la classe che crea un utente a partire dal nome, dalla data di nascita, e dal indirizzo di residenza.
Nella creazione di un istanza la classe va anche a generare il report relativo all’ utente andando a inserire primariamente le informazioni dell’utente elencate prima, e successivamente va anche a creare l’ account per l’utente stesso 
Questa classe si occupa delle operazione che un utente può andare a eseguire, infatti può andare a eseguire delle transazioni con i relativi metodi che si rifanno sia a operazioni del conto proprio dell’ utente, sia per operazioni verso altri utenti
Infatti in questa classe viene definito un vettore di unique_ptr di Account “rubrica” che salva in memoria gli account degli utenti con cui va a eseguire delle operazioni cosi da velocizzare le successive operazioni tra l’utente stesso e gli altri utenti già salvati in rubrica
Questa classe ha anche il compito di andare sia a stampare le informazioni relative all’ utente, sia le informazioni relative alle transazioni eseguite
Successivamente questa classe si occupa anche di andare a eliminare l’account stesso dell’utente e quindi anche della cancellazione effettiva del’ report dell’ utente
Infine la classe oltre che a tutte le informazioni dell’ utente e delle sue transazioni, può anche andare a leggere il report intero creato.
