#include <opencv2/sfm.hpp>
#include <opencv2/viz.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace cv;
using namespace cv::sfm;

const String keys =
"{help h usage ? help  |     | Help message   }"
"{f  | 1428    | focal value   }"
"{x  |  640    | cx is the image principal point x coordinates in pixels.   }"
"{y  |  480    | cy is the image principal point y coordinates in pixels.   }"
"{@arg1 |     | empty = simulate data saved in myMatchdata.yml}";


int main (int argc,char **argv)
{
    CommandLineParser parser(argc, argv, keys);

    if (parser.has("help"))
    {
        parser.printMessage();
        return 0;
    }
    String nomFic = parser.get<String>(0);
    vector<Mat> pt2d1;
    vector<Mat> pt3d1;
    Matx33d K = Matx33d( 1428, 0, 640, 0, 1428, 480, 0, 0, 1);
    if (parser.has("f"))
    {
        K(0, 0) = parser.get<double>("f");
        K(1, 1) = K(0, 0);
    }
    if (parser.has("x"))
    {
        K(0, 2) = parser.get<double>("x");
    }
    if (parser.has("y"))
    {
        K(1, 2) = parser.get<double>("y");
    }
    if (nomFic.length() == 0)
    {
        pt2d1.push_back((Mat_<double>(1, 216) << 1028.8265208422474, 630.75473327994234, 1029.9623410162367, 628.67047008772204, 1033.8855507029073, 621.47126573077719, 1040.2650684237346, 609.76466439182002, 1048.4800533196403, 594.6899271796392, 1057.67755340346, 577.81224590213685, 1066.8749263994853, 560.93479783444945, 1075.089582891565, 545.86066325288073, 1081.4687057168005, 534.15478655886807, 1085.3916118364564, 526.95613925626117, 1028.8265208422474, 630.75473327994234, 1042.6210649116142, 635.77913663139668, 1058.2767721615944, 635.11272797936954, 1074.21275121699, 628.62501281049708, 1088.716306279503, 616.8526564146573, 1100.1695865815918, 600.99217884301265, 1107.2898612349959, 582.76830122534409, 1109.3232390659123, 564.19410174213567, 1106.1411114771274, 547.27816766005208, 1098.2204929066636, 533.75129537641021, 1028.8265208422474, 630.75473327994234, 1050.5113416641682, 639.95427767176307, 1073.3794629073186, 643.13787002982929, 1095.0866253501956, 639.79458913165013, 1113.2950809989484, 630.12478679472406, 1125.9859344083973, 615.07531788451263, 1131.7541276864013, 596.24975639745298, 1130.013945179634, 575.69850980844853, 1121.0638497359391, 555.63225549034769, 1106.0019832556338, 538.12528756263589, 1028.8265208422474, 630.75473327994234, 1050.5557099545015, 639.56953663873571, 1073.1937204909029, 642.36511438018294, 1094.4753756517703, 638.78182172965023, 1112.2243137486491, 629.11764825424234, 1124.6020757977692, 614.32040578935505, 1130.3280000880559, 595.89479610377475, 1128.832027152311, 575.73304654345543, 1120.3140614945582, 555.89461970733043, 1105.7028037736306, 538.37099193358495, 1028.8265208422474, 630.75473327994234, 1042.8631608146595, 634.84707689081199, 1058.2584967688865, 633.36513780784253, 1073.5201808839392, 626.49673981988565, 1087.1901914406481, 614.93311570256458, 1097.9739086020063, 599.79440917844522, 1104.8505533469176, 582.52462490041466, 1107.1601342595291, 564.76447800316646, 1104.6630875159808, 548.20938486875832, 1097.5686227034093, 534.45972996765431, 1028.8265208422474, 630.75473327994234, 1030.5094451565753, 627.66651801138744, 1034.7710087258772, 619.84642439779543, 1041.1508028774458, 608.13931580035444, 1049.0276032399836, 593.68515708397672, 1057.6775534034603, 577.81224590213697, 1066.3273911603369, 561.93954098969016, 1074.203893598404, 547.48592897341746, 1080.5833098120127, 535.77951390317128, 1084.8445528041379, 527.96000855806108, 1028.8265208422474, 630.75473327994234, 1018.1741780167231, 620.74342676475555, 1011.5526455838799, 606.87287620359348, 1009.432325764166, 590.53374347926467, 1011.8840276047719, 573.23767041426277, 1018.6183086835936, 556.50494178862834, 1029.0286987776246, 541.7778391792624, 1042.2318549174643, 530.34751728162291, 1057.1072904756345, 523.28067419880733, 1072.346767864846, 521.33634501543634, 1028.8265208422474, 630.75473327994234, 1010.4101690965293, 616.63109420608566, 996.9054207091491, 599.07749404652373, 989.41722948906693, 579.80687553297571, 988.48495091991276, 560.59034617421696, 994.09748444298839, 543.12852698707104, 1005.7283601637679, 528.95005419427048, 1022.3782374179993, 519.32551513551607, 1042.6242747915535, 515.18516094478298, 1064.6864339428105, 517.0345166093, 1028.8265208422474, 630.75473327994234, 1010.1203860471132, 616.86908165559817, 996.19985447065733, 599.3243841996026, 988.33023759751575, 579.83863843873178, 987.19255503865372, 560.26867143621132, 992.84977172120693, 542.44788416870733, 1004.7580535827984, 528.03740660115034, 1021.816137753751, 518.39418344227761, 1042.44951185794, 514.45808391571939, 1064.7294016570784, 516.66192071592866, 1028.8265208422474, 630.75473327994234, 1017.5350185621438, 621.43804766425978, 1010.129091420788, 607.7697751504603, 1007.3782941632923, 591.07535887445397, 1009.5887692661379, 573.00838401730766, 1016.5588223557643, 555.38146636509168, 1027.592783283955, 539.971750817464, 1041.5742740659934, 528.32676718803498, 1057.0896910577135, 521.59772432873001, 1072.5841040247224, 520.42261009954859, 1023.6872850276745, 501.48463396235769, 1021.7363061422241, 497.10356942867941, 1149.394888427619, 563.63353085150766, 1144.1773056475884, 564.44012449568231, 975.13608212288557, 590.57245094776658, 970.39817079227953, 591.3048914910305, 1095.4493161212483, 662.63147754605677, 1093.3004875390534, 657.80612717419194));
        pt2d1.push_back((Mat_<double>(1, 216) << 1067.8928935365691, 683.58145840030193, 1068.4581827905051, 681.10599202818446, 1071.882360816011, 673.41459952541288, 1077.8853119590685, 661.16770635223315, 1085.8867161323376, 645.56367742058092, 1095.0583596138767, 628.22462933245185, 1104.4226038828747, 611.0007252018562, 1112.9805870843823, 595.7267800366983, 1119.8434591346158, 583.9821639253181, 1124.339246882791, 576.90376658902449, 1067.8928935365691, 683.58145840030193, 1081.7151834279362, 688.66941795050138, 1097.428138122013, 687.9235640959464, 1113.4424085464443, 681.21495349585223, 1128.0331376073316, 669.10149841032887, 1139.5697153845745, 652.81908590227658, 1146.7592402475202, 634.14365737410071, 1148.8421591563374, 615.14204082571655, 1145.6886794245606, 597.86975221760406, 1137.7775035660395, 584.09118932755541, 1067.8928935365691, 683.58145840030193, 1090.2068754511652, 693.25377638834675, 1113.7045025864693, 696.73875324851565, 1135.9666313492651, 693.47911129723286, 1154.5812316896593, 683.65703206786213, 1167.4712118672201, 668.23587408124456, 1173.2032121184857, 648.86845178433623, 1171.1998404776273, 627.67681432581799, 1161.8014456750811, 606.95060334736809, 1146.1703105477263, 588.83599644775961, 1067.8928935365691, 683.58145840030193, 1090.6099121354423, 693.06659141864566, 1114.2030661855272, 696.34057932339863, 1136.2995604798953, 692.98103060973449, 1154.6227836605078, 683.25516008272655, 1167.2593380673673, 668.11880460810607, 1172.8939515366988, 649.12207352093083, 1170.9695166353083, 628.23058679082555, 1161.7434641884424, 607.59086467825603, 1146.2344983602861, 589.28038302494531, 1067.8928935365691, 683.58145840030193, 1082.895229343043, 688.25541702053886, 1099.1987117243582, 687.16019827974128, 1115.2184652848321, 680.44120103891714, 1129.416340908339, 668.77583871340801, 1140.4400477713136, 653.29998233232993, 1147.2414182318191, 635.49918384908153, 1149.1674409826339, 617.07431697162906, 1146.0193774849595, 599.79068436161003, 1138.0759557114482, 585.31963542080052, 1067.8928935365691, 683.58145840030193, 1070.16214258433, 680.7438161718253, 1074.9706987700099, 673.01147203970811, 1081.8081309064039, 661.22558916810021, 1090.0119148330264, 646.53931741824908, 1098.8284111281616, 630.3077464747771, 1107.4681971595389, 613.98627365569405, 1115.1570019568696, 599.03595733299926, 1121.1859294113658, 586.82933555112163, 1124.9644691622577, 578.54988864786185, 1067.8928935365691, 683.58145840030193, 1057.2452316565234, 673.379002774985, 1050.6581082937757, 659.2168370609121, 1048.5949446531069, 642.51881388549361, 1051.1173521145827, 624.83125168341883, 1057.9265533613118, 607.70769426216475, 1068.4082059460577, 592.62090547512094, 1081.6734323750627, 580.88938431356303, 1096.5986443721899, 573.60396841771808, 1111.8743379295613, 571.54415939325634, 1067.8928935365691, 683.58145840030193, 1048.9111776957698, 668.87652125259319, 1034.9508983701969, 650.70004084883863, 1027.1453920233062, 630.82629923276181, 1026.0481077210379, 611.07674253688992, 1031.6521368358715, 593.18993840091048, 1043.4286548389177, 578.721352989053, 1060.3705768160517, 568.95955884346415, 1081.0406285772904, 564.84568295355064, 1103.6344924420018, 566.88907690249778, 1067.8928935365691, 683.58145840030193, 1048.265471923263, 668.91569517314667, 1033.5708399191926, 650.56828363936381, 1025.1325099110034, 630.33712363016298, 1023.6682637307592, 610.14373701169086, 1029.2596225384095, 591.86797037808185, 1041.3659575359936, 577.19994258568397, 1058.8746289112819, 567.51082846526663, 1080.1834791017463, 563.7425119513822, 1103.3167108254768, 566.31844609073255, 1067.8928935365691, 683.58145840030193, 1055.6725753643061, 673.55353662991126, 1047.4617229934086, 659.1230163588009, 1044.1023768200268, 641.69608789417691, 1045.9539738614085, 622.99882697990961, 1052.846211261882, 604.90058468392704, 1064.0913680793378, 589.21585788732568, 1078.5566817649235, 577.50998282342039, 1094.7877055131692, 570.93429704431423, 1111.1655984212562, 570.11146605475471, 1068.8704743613182, 554.53428611501374, 1063.9450442024581, 548.49498043087226, 1197.081473717712, 618.60987666117319, 1194.8324071076543, 621.05020507745462, 1019.7936007286088, 645.91900575138266, 1012.1103123788265, 644.99848015359839, 1142.5378403469267, 720.52183104654694, 1143.3339670100315, 717.27046330120515));
        pt2d1.push_back((Mat_<double>(1, 216) << 1106.5208711485714, 741.50000049355288, 1106.4689494686579, 738.58802914804187, 1109.3501259102466, 730.34841486744574, 1114.939395472757, 717.50083145458598, 1122.7004345574444, 701.30948584821124, 1131.8323058505634, 683.45951438933207, 1141.3637728209014, 665.85274339228056, 1150.2798129066516, 650.35860912193448, 1157.654291765783, 638.57201851568459, 1162.7613665256426, 631.62736960308541, 1106.5208711485714, 741.50000049355288, 1120.3576643153483, 746.66233373712521, 1136.1131687270374, 745.83122124275212, 1152.1907277068667, 738.87977804315722, 1166.8548613344165, 726.38981283804787, 1178.4639850307283, 709.64090998541531, 1185.7167117214517, 690.46542969064296, 1187.8489642622787, 670.98913405384258, 1184.7299946431201, 653.31896453575837, 1176.8394080426426, 639.25639203125183, 1106.5208711485714, 741.50000049355288, 1129.4905019784496, 751.70595049127405, 1153.6411068866935, 755.53315567927564, 1176.4749364071429, 752.37245531571841, 1195.5026704255715, 742.38555549078183, 1208.5876644980842, 726.55387522300271, 1214.2690551999476, 706.58461409952679, 1211.9804962119542, 684.67907150122062, 1202.1079825941652, 663.21439810764696, 1185.881631332802, 644.41676223228831, 1106.5208711485714, 741.50000049355288, 1130.2816201445758, 751.73986447744915, 1154.8819119236368, 755.55485038277197, 1177.8340777125179, 752.45173594258813, 1196.7548671941956, 742.66256661276918, 1209.6520720905519, 727.15148776331444, 1215.1755732276433, 707.51891694710991, 1212.7846911708384, 685.81227694750123, 1202.8005491756587, 664.27533636692294, 1186.3390344595209, 645.08180588222297, 1106.5208711485714, 741.50000049355288, 1122.5515511825249, 746.82761962544794, 1139.8201658767964, 746.16917289632045, 1156.642272397497, 739.62184522445341, 1171.3937108991886, 727.84689043988749, 1182.6609656186304, 711.99730827543624, 1189.3680088375486, 693.60494724925832, 1190.8715188535589, 674.43800530797739, 1187.0188831430844, 656.34006932374371, 1178.1651450666627, 641.06195459560911, 1106.5208711485714, 741.50000049355288, 1109.4213665179313, 738.942490402668, 1114.8156966255365, 731.30875824877501, 1122.1395480082178, 719.4356479964805, 1130.6861646984178, 704.49107197154171, 1139.6704433829484, 687.86024331609917, 1148.2865730511819, 671.03948954728151, 1155.7605151950252, 655.53708703172401, 1161.4009144024665, 642.77508963113996, 1164.6516661899932, 633.98548023803164, 1106.5208711485714, 741.50000049355288, 1095.888877842398, 731.08056490025206, 1089.3443232179313, 716.58925490028514, 1087.3431873190796, 699.48748020128835, 1089.937488126664, 681.36098683620844, 1096.8188118655555, 663.80115866765982, 1107.3648302571987, 648.31526172567021, 1120.681335602038, 636.25236401317989, 1135.6422893941292, 628.72976171505582, 1150.9381011214252, 626.54880853087161, 1106.5208711485714, 741.50000049355288, 1086.9477908605254, 726.14040693438278, 1072.5091441840091, 707.26334098821826, 1064.3682972296936, 686.71212108746306, 1063.0935246982247, 666.36508530578703, 1068.6822113164806, 648.00384056426958, 1080.6029742421242, 633.21424662976324, 1097.8407506285969, 623.30494885594453, 1118.9437256647429, 619.22864040167235, 1142.0832991181603, 621.49783517673097, 1106.5208711485714, 741.50000049355288, 1085.9189387790498, 725.95804717534497, 1070.4046077909045, 706.71063351618943, 1061.3626385909047, 685.64500727464826, 1059.549001127127, 664.75501330148461, 1065.0641315983587, 645.97246665572288, 1077.3704640568426, 631.01993557205321, 1095.343720015409, 621.28440625154815, 1117.3537917095414, 617.70965704428454, 1141.3772373302338, 620.70804205286834, 1106.5208711485714, 741.50000049355288, 1093.3103773516757, 730.67511576758284, 1084.2404067245163, 715.39246043362039, 1080.2297722966712, 697.14833333534295, 1081.6938714349671, 677.74938750464776, 1088.495147990049, 659.12783056614569, 1099.9542841662278, 643.13940976689821, 1114.9219559561584, 631.3690047401102, 1131.9020534613658, 624.96787278972988, 1149.2100735166773, 624.54142364562324, 1114.1024784807053, 612.6686031148048, 1105.9543529343073, 604.7786513745275, 1244.9176353203754, 678.98321712381755, 1245.9389065801597, 683.26656884018348, 1064.520450250835, 706.63622233985939, 1053.6455115183364, 703.86051265866729, 1189.8275589862967, 784.15460376850683, 1193.8651240470415, 782.69395098725897));
        pt2d1.push_back((Mat_<double>(1, 216) << 1144.6799579195197, 804.85899215438599, 1143.9597472311048, 801.45615222480399, 1146.2503200861136, 792.60170439960677, 1151.386286071991, 779.08209481052711, 1158.8789841666487, 762.23526759569415, 1167.957314892026, 743.81648237240574, 1177.657733666761, 725.78466435057828, 1186.9489788693654, 710.04721863137911, 1194.8661499864766, 698.21586121499172, 1200.6267024845697, 691.42197303837008, 1144.6799579195197, 804.85899215438599, 1158.5160739755199, 810.10631154210353, 1174.2977751685303, 809.18138778719697, 1190.4224268078813, 801.96015724971016, 1205.1456152938981, 789.05154254676324, 1216.8166600457232, 771.78394697171677, 1224.1273841627517, 752.05222572939851, 1226.3102367191289, 732.0470826384385, 1223.2335679010871, 713.93204578873952, 1215.376869789915, 699.54958368383143, 1144.6799579195197, 804.85899215438599, 1168.3332071698312, 815.66789965943553, 1193.1618112391507, 819.88352114929296, 1216.5854258231366, 816.83848261960554, 1236.0342158693431, 806.67141829418438, 1249.3105318879079, 790.38368889584854, 1254.92684751455, 769.74291033211875, 1252.330717581191, 747.03849451679321, 1241.9576878712512, 724.7450099106378, 1225.109494772335, 705.177970657694, 1144.6799579195197, 804.85899215438599, 1169.5447851179513, 815.95139840664217, 1195.2086826047205, 820.37993340617243, 1219.0611600029742, 817.57108829243498, 1238.605316677829, 807.71657371010372, 1251.7658930832661, 791.7891565109727, 1257.1576739275433, 771.44529738176789, 1254.2601956732801, 748.82407495030088, 1243.4649305830681, 726.27843321336979, 1225.9926200811412, 706.09026769440447, 1144.6799579195197, 804.85899215438599, 1161.8072909486764, 810.9249341669306, 1180.1035632795956, 810.7623449423071, 1197.7769433694077, 804.41329276974238, 1213.1107066800409, 792.5200045942355, 1224.626156823643, 776.25416293527189, 1231.2188869718441, 757.19944867026038, 1232.2582618308122, 737.19980624497805, 1227.6436061825525, 718.18700644127875, 1217.8136555014084, 702.00135723624044, 1144.6799579195197, 804.85899215438599, 1148.2612968149381, 802.61772678180284, 1154.2845901355347, 795.09682785773452, 1162.1272674987097, 783.12790359244525, 1171.035004578737, 767.89531033708806, 1180.1893147778871, 750.81817309729092, 1188.7677202470613, 733.43896315551581, 1195.9978206416067, 717.31910595095633, 1201.2087481750307, 703.93620386281168, 1203.8829751426558, 694.57641320455878, 1144.6799579195197, 804.85899215438599, 1134.0766538615242, 794.19448914447923, 1127.584774582986, 779.3321377296553, 1125.6522337408283, 761.77581066097287, 1128.3209196636617, 743.15606804803065, 1135.2723715693394, 725.1073696646489, 1145.8760897302259, 709.17612599424615, 1159.2327097052976, 696.74575827982142, 1174.2144083283906, 688.96281915046029, 1189.5127519988655, 686.65228386928698, 1144.6799579195197, 804.85899215438599, 1124.4883354349502, 788.76090455651968, 1109.547762062879, 769.09425243127066, 1101.0533286546779, 747.7801985433922, 1099.5888286190609, 726.76145800702534, 1105.1559446592012, 707.86849548781618, 1117.2204078289783, 692.72166042370679, 1134.7588182648435, 682.65212106839897, 1156.3046068679428, 678.62503280920305, 1180.0048170075729, 681.15544828245538, 1144.6799579195197, 804.85899215438599, 1123.0464597501648, 788.32957894410936, 1106.6639980337086, 768.06956086618607, 1096.9817867117599, 746.06641911856377, 1094.7953883438952, 724.39507335235191, 1100.2243802196886, 705.04563010868708, 1112.7339384999332, 689.77708373051098, 1131.1877106190773, 679.99409033671179, 1153.927194801212, 676.64226390655654, 1178.880585595097, 680.12095613471126, 1144.6799579195197, 804.85899215438599, 1130.41286742641, 793.13671275341562, 1120.4256525013209, 776.89686510578474, 1115.7184694561788, 757.73673975171107, 1116.7653977109392, 737.55291853289179, 1123.4628768709858, 718.34752415560683, 1135.1402594330102, 702.02205640044758, 1150.6312849068274, 690.18296980545597, 1168.3971891437905, 683.98124215966754, 1186.6859081512343, 684.00282795803957, 1159.415146412372, 676.26466184556671, 1147.7678313863694, 666.28917121633128, 1292.9367505963062, 745.16752616362146, 1297.5680689427561, 751.55157573423412, 1109.3491796675462, 773.14941258639658, 1095.005989177668, 768.27146044210917, 1237.3558368456218, 854.00307602051817, 1244.9713572637831, 854.60076819605888));

        for (int i = 0; i<pt2d1.size(); i++)
            pt2d1[i] = pt2d1[i].reshape(1, 108).t();
        FileStorage fs("myMatchdata.yml",FileStorage::WRITE);
        fs<<"ptTrack"<<pt2d1;
    }
    else
    {
        FileStorage fs("myMatchdata.yml", FileStorage::READ);
        if (fs.isOpened())
        {
            if (!fs["ptTrack"].empty())
            {
                fs["ptTrack"]>>pt2d1;
            }
            else
            {
                cout<<"node ptTrack not found!\n";
                return 0;
            }
        }
        else
        {
            cout << "File not found!\n";
            return 0;
        }

    }
    vector<Mat> Rs_est1, ts_est1;
    Mat Kr(K);
    reconstruct(pt2d1, Rs_est1, ts_est1, Kr, pt3d1, true);

    // Print output

    cout << "\n----------------------------\n" << endl;
    cout << "Reconstruction: " << endl;
    cout << "============================" << endl;
    cout << "Estimated 3D points: " << pt3d1.size() << endl;
    cout << "Estimated cameras: " << Rs_est1.size() << endl;
    cout << "Refined intrinsics: " << endl << K << endl << endl;
    vector<Mat> pt3d2;
    vector<Mat> Rs_est2, ts_est2;
    if (nomFic == "")
    {
        vector<Mat> pt2d2(pt2d1.size());
        for (int i = 0; i<pt2d2.size(); i++)
            pt2d2[i] = pt2d1[i] / 2 - 50;
        reconstruct(pt2d2, Rs_est2, ts_est2, Kr, pt3d2, true);
    }

    cout << "3D Visualization: " << endl;
    cout << "============================" << endl;
    /// Create 3D windows
    viz::Viz3d window("Coordinate Frame");
    window.setWindowSize(Size(500, 500));
    window.setWindowPosition(Point(150, 150));
    window.setBackgroundColor(); // black by default
// Create the pointcloud
    cout << "Recovering points  ... ";
// recover estimated points3d
    vector<Vec3f> point_cloud_est;
    vector<Vec3b> color;
    for (int i = 0; i < pt3d1.size(); ++i)
    {
        point_cloud_est.push_back(Vec3f(pt3d1[i]));
        color.push_back(Vec3b(0, 255, 0));
    }
    for (int i = 0; i < pt3d2.size(); ++i)
    {
        point_cloud_est.push_back(Vec3f(pt3d2[i]));
        color.push_back(Vec3b(255, 0, 0));
    }
    cout << "[DONE]" << endl;
    /// Recovering cameras
    cout << "Recovering cameras ... ";
    vector<Affine3d> path;
    for (size_t i = 0; i < Rs_est1.size(); ++i)
        path.push_back(Affine3d(Rs_est1[i], ts_est1[i]));
    for (size_t i = 0; i < Rs_est2.size(); ++i)
        path.push_back(Affine3d(Rs_est2[i], ts_est2[i]));
    cout << "[DONE]" << endl;
    /// Add the pointcloud
    if (point_cloud_est.size() > 0)
    {
        cout << "Rendering points   ... ";
        viz::WCloud cloud_widget(point_cloud_est, color);
        window.showWidget("point_cloud", cloud_widget);
        cout << "[DONE]" << endl;
    }
    else
    {
        cout << "Cannot render points: Empty pointcloud" << endl;
    }
    /// Add cameras
    if (path.size() > 0)
    {
        cout << "Rendering Cameras  ... ";
        window.showWidget("cameras_frames_and_lines", viz::WTrajectory(path, viz::WTrajectory::BOTH, 0.1, viz::Color::green()));
        window.showWidget("cameras_frustums", viz::WTrajectoryFrustums(path, K, 0.1, viz::Color::yellow()));
        window.setViewerPose(path[0]);
        cout << "[DONE]" << endl;
    }
    else
    {
        cout << "Cannot render the cameras: Empty path" << endl;
    }

    /// Wait for key 'q' to close the window
    cout << endl << "Press 'q' to close each windows ... " << endl;
    window.spin();
    return 0;
}