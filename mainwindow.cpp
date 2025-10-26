#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    prepareCountryList();
    populateCountryList();
    api_key = "02a26161094176930b30168e";
    //
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnGetRate_clicked()
{
    QString sourceCountry = ui->comboBoxSourceCountry->currentText().split(",")[2].trimmed();
    QString destinationCountry = ui->comboBoxDestinationCountry->currentText().split(",")[2].trimmed();

    getExchangeRateData(sourceCountry);

    qDebug() << "Source Country: " << sourceCountry << ", Destination Country: " << destinationCountry;
}

void MainWindow::prepareCountryList()
{
    countryList = {
        "AFGHANISTAN, Afghani, AFN, 971",
        "ALAND ISLANDS, Euro, EUR, 978",
        "ALBANIA, Lek, ALL, 008",
        "ALGERIA, Algerian Dinar, DZD, 012",
        "AMERICAN SAMOA, US Dollar, USD, 840",
        "ANDORRA, Euro, EUR, 978",
        "ANGOLA, Kwanza, AOA, 973",
        "ANGUILLA, East Caribbean Dollar, XCD, 951",
        "ANTIGUA AND BARBUDA, East Caribbean Dollar, XCD, 951",
        "ARGENTINA, Argentine Peso, ARS, 032",
        "ARMENIA, Armenian Dram, AMD, 051",
        "ARUBA, Aruban Florin, AWG, 533",
        "AUSTRALIA, Australian Dollar, AUD, 036",
        "AUSTRIA, Euro, EUR, 978",
        "AZERBAIJAN, Azerbaijan Manat, AZN, 944",
        "BAHAMAS, Bahamian Dollar, BSD, 044",
        "BAHRAIN, Bahraini Dinar, BHD, 048",
        "BANGLADESH, Taka, BDT, 050",
        "BARBADOS, Barbados Dollar, BBD, 052",
        "BELARUS, Belarusian Ruble, BYN, 933",
        "BELGIUM, Euro, EUR, 978",
        "BELIZE, Belize Dollar, BZD, 084",
        "BENIN, CFA Franc BCEAO, XOF, 952",
        "BERMUDA, Bermudian Dollar, BMD, 060",
        "BHUTAN, Ngultrum, BTN, 064",
        "BHUTAN, Indian Rupee, INR, 356",
        "BOLIVIA, Boliviano, BOB, 068",
        "BOSNIA AND HERZEGOVINA, Convertible Mark, BAM, 977",
        "BOTSWANA, Pula, BWP, 072",
        "BRAZIL, Brazilian Real, BRL, 986",
        "BRITISH INDIAN OCEAN TERRITORY, US Dollar, USD, 840",
        "BRUNEI DARUSSALAM, Brunei Dollar, BND, 096",
        "BULGARIA, Bulgarian Lev, BGN, 975",
        "BURKINA FASO, CFA Franc BCEAO, XOF, 952",
        "BURUNDI, Burundi Franc, BIF, 108",
        "CABO VERDE, Cabo Verde Escudo, CVE, 132",
        "CAMBODIA, Riel, KHR, 116",
        "CAMEROON, CFA Franc BEAC, XAF, 950",
        "CANADA, Canadian Dollar, CAD, 124",
        "CAYMAN ISLANDS, Cayman Islands Dollar, KYD, 136",
        "CENTRAL AFRICAN REPUBLIC, CFA Franc BEAC, XAF, 950",
        "CHAD, CFA Franc BEAC, XAF, 950",
        "CHILE, Chilean Peso, CLP, 152",
        "CHINA, Yuan Renminbi, CNY, 156",
        "COLOMBIA, Colombian Peso, COP, 170",
        "COMOROS, Comorian Franc, KMF, 174",
        "CONGO, CFA Franc BEAC, XAF, 950",
        "CONGO, DEMOCRATIC REPUBLIC OF, Congolese Franc, CDF, 976",
        "COOK ISLANDS, New Zealand Dollar, NZD, 554",
        "COSTA RICA, Costa Rican Colon, CRC, 188",
        "CÔTE D'IVOIRE, CFA Franc BCEAO, XOF, 952",
        "CROATIA, Kuna, HRK, 191",
        "CUBA, Cuban Peso, CUP, 192",
        "CYPRUS, Euro, EUR, 978",
        "CZECHIA, Czech Koruna, CZK, 203",
        "DENMARK, Danish Krone, DKK, 208",
        "DJIBOUTI, Djibouti Franc, DJF, 262",
        "DOMINICA, East Caribbean Dollar, XCD, 951",
        "DOMINICAN REPUBLIC, Dominican Peso, DOP, 214",
        "ECUADOR, US Dollar, USD, 840",
        "EGYPT, Egyptian Pound, EGP, 818",
        "EL SALVADOR, US Dollar, USD, 840",
        "EQUATORIAL GUINEA, CFA Franc BEAC, XAF, 950",
        "ERITREA, Nakfa, ERN, 232",
        "ESTONIA, Euro, EUR, 978",
        "ESWATINI, Lilangeni, SZL, 748",
        "ETHIOPIA, Ethiopian Birr, ETB, 230",
        "EUROPEAN UNION, Euro, EUR, 978",
        "FIJI, Fiji Dollar, FJD, 242",
        "FINLAND, Euro, EUR, 978",
        "FRANCE, Euro, EUR, 978",
        "GABON, CFA Franc BEAC, XAF, 950",
        "GAMBIA, Dalasi, GMD, 270",
        "GEORGIA, Lari, GEL, 981",
        "GERMANY, Euro, EUR, 978",
        "GHANA, Ghana Cedi, GHS, 936",
        "GIBRALTAR, Gibraltar Pound, GIP, 292",
        "GREECE, Euro, EUR, 978",
        "GREENLAND, Danish Krone, DKK, 208",
        "GRENADA, East Caribbean Dollar, XCD, 951",
        "GUADELOUPE, Euro, EUR, 978",
        "GUAM, US Dollar, USD, 840",
        "GUATEMALA, Quetzal, GTQ, 320",
        "GUERNSEY, Pound Sterling, GBP, 826",
        "GUINEA, Guinean Franc, GNF, 324",
        "GUINEA-BISSAU, CFA Franc BCEAO, XOF, 952",
        "GUYANA, Guyana Dollar, GYD, 328",
        "HAITI, Gourde, HTG, 332",
        "HAITI, US Dollar, USD, 840",
        "HEARD ISLAND AND MCDONALD ISLANDS, Australian Dollar, AUD, 036",
        "HOLY SEE (VATICAN CITY STATE), Euro, EUR, 978",
        "HONDURAS, Lempira, HNL, 340",
        "HONG KONG, Hong Kong Dollar, HKD, 344",
        "HUNGARY, Forint, HUF, 348",
        "ICELAND, Iceland Krona, ISK, 352",
        "INDIA, Indian Rupee, INR, 356",
        "INDONESIA, Rupiah, IDR, 360",
        "IRAN, Iranian Rial, IRR, 364",
        "IRAQ, Iraqi Dinar, IQD, 368",
        "IRELAND, Euro, EUR, 978",
        "ISLE OF MAN, Pound Sterling, GBP, 826",
        "ISRAEL, New Israeli Sheqel, ILS, 376",
        "ITALY, Euro, EUR, 978",
        "JAMAICA, Jamaican Dollar, JMD, 388",
        "JAPAN, Yen, JPY, 392",
        "JERSEY, Pound Sterling, GBP, 826",
        "JORDAN, Jordanian Dinar, JOD, 400",
        "KAZAKHSTAN, Tenge, KZT, 398",
        "KENYA, Kenyan Shilling, KES, 404",
        "KIRIBATI, Australian Dollar, AUD, 036",
        "KOREA (NORTH), North Korean Won, KPW, 408",
        "KOREA (SOUTH), Won, KRW, 410",
        "KUWAIT, Kuwaiti Dinar, KWD, 414",
        "KYRGYZSTAN, Som, KGS, 417",
        "LAOS, Kip, LAK, 418",
        "LATVIA, Euro, EUR, 978",
        "LEBANON, Lebanese Pound, LBP, 422",
        "LESOTHO, Loti, LSL, 426",
        "LESOTHO, Rand, ZAR, 710",
        "LIBERIA, Liberian Dollar, LRD, 430",
        "LIBYA, Libyan Dinar, LYD, 434",
        "LIECHTENSTEIN, Swiss Franc, CHF, 756",
        "LITHUANIA, Euro, EUR, 978",
        "LUXEMBOURG, Euro, EUR, 978",
        "MACAO, Pataca, MOP, 446",
        "MACEDONIA, Denar, MKD, 807",
        "MADAGASCAR, Ariary, MGA, 969",
        "MALAWI, Malawi Kwacha, MWK, 454",
        "MALAYSIA, Malaysian Ringgit, MYR, 458",
        "MALDIVES, Rufiyaa, MVR, 462",
        "MALI, CFA Franc BCEAO, XOF, 952",
        "MALTA, Euro, EUR, 978",
        "MARSHALL ISLANDS, US Dollar, USD, 840",
        "MARTINIQUE, Euro, EUR, 978",
        "MAURITANIA, Ouguiya, MRU, 929",
        "MAURITIUS, Mauritius Rupee, MUR, 480",
        "MEXICO, Mexican Peso, MXN, 484",
        "MICRONESIA, US Dollar, USD, 840",
        "MOLDOVA, Moldovan Leu, MDL, 498",
        "MONACO, Euro, EUR, 978",
        "MONGOLIA, Tugrik, MNT, 496",
        "MONTENEGRO, Euro, EUR, 978",
        "MONTSERRAT, East Caribbean Dollar, XCD, 951",
        "MOROCCO, Moroccan Dirham, MAD, 504",
        "MOZAMBIQUE, Mozambique Metical, MZN, 943",
        "MYANMAR, Kyat, MMK, 104",
        "NAMIBIA, Namibia Dollar, NAD, 516",
        "NAMIBIA, Rand, ZAR, 710",
        "NAURU, Australian Dollar, AUD, 036",
        "NEPAL, Nepalese Rupee, NPR, 524",
        "NETHERLANDS, Euro, EUR, 978",
        "NEW CALEDONIA, CFP Franc, XPF, 953",
        "NEW ZEALAND, New Zealand Dollar, NZD, 554",
        "NICARAGUA, Cordoba Oro, NIO, 558",
        "NIGER, CFA Franc BCEAO, XOF, 952",
        "NIGERIA, Naira, NGN, 566",
        "NIUE, New Zealand Dollar, NZD, 554",
        "NORFOLK ISLAND, Australian Dollar, AUD, 036",
        "NORTHERN MARIANA ISLANDS, US Dollar, USD, 840",
        "NORWAY, Norwegian Krone, NOK, 578",
        "OMAN, Rial Omani, OMR, 512",
        "PAKISTAN, Pakistan Rupee, PKR, 586",
        "PALAU, US Dollar, USD, 840",
        "PALESTINE, Israeli New Shekel, ILS, 376",
        "PANAMA, Balboa, PAB, 590",
        "PANAMA, US Dollar, USD, 840",
        "PAPUA NEW GUINEA, Kina, PGK, 598",
        "PARAGUAY, Guarani, PYG, 600",
        "PERU, Nuevo Sol, PEN, 604",
        "PHILIPPINES, Philippine Peso, PHP, 608",
        "PITCAIRN, New Zealand Dollar, NZD, 554",
        "POLAND, Zloty, PLN, 985",
        "PORTUGAL, Euro, EUR, 978",
        "PUERTO RICO, US Dollar, USD, 840",
        "QATAR, Qatari Rial, QAR, 634",
        "RÉUNION, Euro, EUR, 978",
        "ROMANIA, Romanian Leu, RON, 946",
        "RUSSIAN FEDERATION, Russian Ruble, RUB, 643",
        "RWANDA, Rwanda Franc, RWF, 646",
        "SAINT BARTHÉLEMY, Euro, EUR, 978",
        "SAINT HELENA, Saint Helena Pound, SHP, 654",
        "SAINT KITTS AND NEVIS, East Caribbean Dollar, XCD, 951",
        "SAINT LUCIA, East Caribbean Dollar, XCD, 951",
        "SAINT MARTIN, Euro, EUR, 978",
        "SAINT PIERRE AND MIQUELON, Euro, EUR, 978",
        "SAINT VINCENT AND THE GRENADINES, East Caribbean Dollar, XCD, 951",
        "SAMOA, Tala, WST, 882",
        "SAN MARINO, Euro, EUR, 978",
        "SAO TOME AND PRINCIPE, Dobra, STN, 930",
        "SAUDI ARABIA, Saudi Riyal, SAR, 682",
        "SENEGAL, CFA Franc BCEAO, XOF, 952",
        "SERBIA, Serbian Dinar, RSD, 941",
        "SEYCHELLES, Seychelles Rupee, SCR, 690",
        "SIERRA LEONE, Leone, SLL, 694",
        "SINGAPORE, Singapore Dollar, SGD, 702",
        "SINT MAARTEN, Netherlands Antillean Guilder, ANG, 532",
        "SLOVAKIA, Euro, EUR, 978",
        "SLOVENIA, Euro, EUR, 978",
        "SOLOMON ISLANDS, Solomon Islands Dollar, SBD, 090",
        "SOMALIA, Somali Shilling, SOS, 706",
        "SOUTH AFRICA, Rand, ZAR, 710",
        "SOUTH GEORGIA AND THE SOUTH SANDWICH ISLANDS, Pound Sterling, GBP, 826",
        "SOUTH SUDAN, South Sudanese Pound, SSP, 728",
        "SPAIN, Euro, EUR, 978",
        "SRI LANKA, Sri Lanka Rupee, LKR, 144",
        "SUDAN, Sudanese Pound, SDG, 938",
        "SURINAME, Surinam Dollar, SRD, 968",
        "SVALBARD AND JAN MAYEN, Norwegian Krone, NOK, 578",
        "SWAZILAND, Lilangeni, SZL, 748",
        "SWEDEN, Swedish Krona, SEK, 752",
        "SWITZERLAND, Swiss Franc, CHF, 756",
        "SYRIAN ARAB REPUBLIC, Syrian Pound, SYP, 760",
        "TAIWAN, New Taiwan Dollar, TWD, 901",
        "TAJIKISTAN, Somoni, TJS, 972",
        "TANZANIA, Tanzanian Shilling, TZS, 834",
        "THAILAND, Baht, THB, 764",
        "TIMOR-LESTE, US Dollar, USD, 840",
        "TOGO, CFA Franc BCEAO, XOF, 952",
        "TOKELAU, New Zealand Dollar, NZD, 554",
        "TONGA, Pa’anga, TOP, 776",
        "TRINIDAD AND TOBAGO, Trinidad and Tobago Dollar, TTD, 780",
        "TUNISIA, Tunisian Dinar, TND, 788",
        "TURKEY, Turkish Lira, TRY, 949",
        "TURKMENISTAN, Turkmenistan New Manat, TMT, 934",
        "TURKS AND CAICOS ISLANDS, US Dollar, USD, 840",
        "TUVALU, Australian Dollar, AUD, 036",
        "UGANDA, Uganda Shilling, UGX, 800",
        "UKRAINE, Hryvnia, UAH, 980",
        "UNITED ARAB EMIRATES, UAE Dirham, AED, 784",
        "UNITED KINGDOM, Pound Sterling, GBP, 826",
        "UNITED STATES MINOR OUTLYING ISLANDS, US Dollar, USD, 840",
        "UNITED STATES, US Dollar, USD, 840",
        "URUGUAY, Peso Uruguayo, UYU, 858",
        "UZBEKISTAN, Uzbekistan Sum, UZS, 860",
        "VANUATU, Vatu, VUV, 548",
        "VENEZUELA, Venezuelan Bolivar, VES, 928",
        "VIETNAM, Dong, VND, 704",
        "VIRGIN ISLANDS (BRITISH), US Dollar, USD, 840",
        "VIRGIN ISLANDS (U.S.), US Dollar, USD, 840",
        "WALLIS AND FUTUNA, CFP Franc, XPF, 953",
        "WESTERN SAHARA, Moroccan Dirham, MAD, 504",
        "YEMEN, Yemeni Rial, YER, 886",
        "ZAMBIA, Zambian Kwacha, ZMW, 967",
        "ZIMBABWE, Zimbabwe Dollar, ZWL, 932"};
}

void MainWindow::populateCountryList()
{
    ui->comboBoxSourceCountry->addItems(countryList);
    ui->comboBoxDestinationCountry->addItems(countryList);
}

void MainWindow::getExchangeRateData(QString sourceCountry)
{
    manager = new QNetworkAccessManager(this);
    QString url = QString("https://v6.exchangerate-api.com/v6/%1/latest/%2").arg(api_key, sourceCountry);
    qDebug() << url;

    QNetworkRequest request((QUrl(url)));
    reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, this, &MainWindow::onDataReceived);

    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << "Network error: " << reply->errorString();
        QMessageBox msgBox;
        msgBox.setText("Network error: No data found!");
        msgBox.exec();
    }
}

void MainWindow::onDataReceived()
{
    qDebug() << "in onDataReceived()";

    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    if (reply->error() == QNetworkReply::NoError)
    {
        qDebug() << "Data Received.";
        QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject jsonObj = jsonDoc.object();
        QString jsonString = jsonDoc.toJson(QJsonDocument::Indented);
        qDebug() << jsonString;
        ui->txtJsonResponse->setText(jsonString);
        QString destinationCountry = ui->comboBoxDestinationCountry->currentText().split(",")[2].trimmed();
        QString sourceCountry = ui->comboBoxSourceCountry->currentText().split(",")[2].trimmed();

        double exchangeRate = jsonObj["conversion_rates"].toObject()[destinationCountry].toDouble();
        qDebug() << "Exchange rate: " << exchangeRate;
        ui->lblExchangeRate->setText("1 " + sourceCountry + " = " + QString::number(exchangeRate) + " " + destinationCountry);
    }
    else
    {
        qDebug() << "Network error: " << reply->errorString();
        qDebug() << reply->readAll();

        QMessageBox msgBox;
        msgBox.setText("No data found: " + reply->errorString());
        msgBox.exec();
    }

    reply->deleteLater();
}
