#include <stdio.h>
#include <stdlib.h>
#define MAX_STRING_LENGTH 6

struct package
{
    char* id;
    int weight;
};

typedef struct package package;

struct post_office
{
    int min_weight;
    int max_weight;
    package* packages;
    int packages_count;
};

typedef struct post_office post_office;

struct town
{
    char* name;
    post_office* offices;
    int offices_count;
};

typedef struct town town;

void print_all_packages(town t) {
    
    printf("%s:\n", t.name);
    for(int i=0; i<t.offices_count; i++){
        printf("\t%d:\n", i);
        for(int j=0; j<t.offices[i].packages_count; j++){
            printf("\t\t%s\n", t.offices[i].packages[j].id);
        }
   
    } 
    
}

void send_all_acceptable_packages(town* source, int source_office_index, town* target, int target_office_index) {
    
    int spNUM = source->offices[source_office_index].packages_count;

    int tMAXWEIGHT = target->offices[target_office_index].max_weight;
    int tMINWEIGHT = target->offices[target_office_index].min_weight;
    
    post_office *tempSourcePTT = (post_office *)malloc(sizeof(post_office)*1);
    tempSourcePTT->packages_count = 0;
    tempSourcePTT->max_weight = source->offices[source_office_index].max_weight;
    tempSourcePTT->min_weight = source->offices[source_office_index].min_weight;

    tempSourcePTT->packages = (package *)malloc(sizeof(package)*(tempSourcePTT->packages_count));

    printf("-----------------------------------------\n");
    printf("Source : %s\n", source->name);
    printf("Target : %s\n", target->name);
    printf("spNUM = %d\t", spNUM);
    printf("tMAXWEIGHT = %d\t", tMAXWEIGHT);
    printf("tMINWEIGHT = %d\t", tMINWEIGHT);
    printf("tempSourcePTT packageCount = %d\t", tempSourcePTT->packages_count);
    printf("tempSourcePTT->max_weight = %d\t", tempSourcePTT->max_weight);
    printf("tempSourcePTT->min_weight = %d\t\n", tempSourcePTT->min_weight);


        
    for(int i=0; i<spNUM; i++){
        int sWEIGHT = source->offices[source_office_index].packages[i].weight;
        if((tMAXWEIGHT>=sWEIGHT) && (tMINWEIGHT <= sWEIGHT)){
            (target->offices[target_office_index].packages_count ) += 1;
            target->offices[target_office_index].packages = (package *)realloc(target->offices[target_office_index].packages, sizeof(package)*(target->offices[target_office_index].packages_count ));
            target->offices[target_office_index].packages[(target->offices[target_office_index].packages_count)-1].id = source->offices[source_office_index].packages[i].id;
            target->offices[target_office_index].packages[(target->offices[target_office_index].packages_count)-1].weight = source->offices[source_office_index].packages[i].weight;
            
            
        }else{
            //add source package to new one
            (tempSourcePTT->packages_count) += 1;
            tempSourcePTT->packages = (package *)realloc(tempSourcePTT->packages, sizeof(package)*(tempSourcePTT->packages_count));
            tempSourcePTT->packages[(tempSourcePTT->packages_count)-1].id = source->offices[source_office_index].packages[i].id;
            tempSourcePTT->packages[(tempSourcePTT->packages_count)-1].weight = source->offices[source_office_index].packages[i].weight;
        }
        
    }
    
    source->offices[source_office_index] = *tempSourcePTT; 
    
    free(tempSourcePTT);
    printf("Source : %s\n", source->name);
    printf("Target : %s\n", target->name);
    printf("spNUM = %d\t", spNUM);
    printf("tMAXWEIGHT = %d\t", tMAXWEIGHT);
    printf("tMINWEIGHT = %d\t", tMINWEIGHT);
    printf("SourcePTT packageCount = %d\t", source->offices[source_office_index].packages_count);
    printf("SourcePTT->max_weight = %d\t", source->offices[source_office_index].max_weight);
    printf("SourcePTT->min_weight = %d\t\n", source->offices[source_office_index].min_weight);
    printf("-----------------------------------------\n");
}

town town_with_most_packages(town* towns, int towns_count) {
    int maxPackageCount = 0;
    int x=0;
    for(int i= 0; i<towns_count; i++){
        int NOPackagesinATown = 0;
        for(int j = 0; j<towns[i].offices_count; j++){
            NOPackagesinATown += towns[i].offices[j].packages_count;
        }
        if( NOPackagesinATown > maxPackageCount){
            x = i;
            maxPackageCount = NOPackagesinATown;  
        }
        
    }
    
    return towns[x];
}

town* find_town(town* towns, int towns_count, char* name) {
    town *ret;
    
    for(int i=0; i<towns_count; i++){
        for(int j=0; towns[i].name[j]!='\0'; j++){
            if(name[j] == towns[i].name[j]){
                ret = towns+i;
                
            }else{
                break;
            }
        }

    }

    return ret;
}

int main()
{
    int towns_count;
    scanf("%d", &towns_count);
    town* towns = malloc(sizeof(town)*towns_count);
    for (int i = 0; i < towns_count; i++) {
        towns[i].name = malloc(sizeof(char) * MAX_STRING_LENGTH);
        scanf("%s", towns[i].name);
        scanf("%d", &towns[i].offices_count);
        towns[i].offices = malloc(sizeof(post_office)*towns[i].offices_count);
        for (int j = 0; j < towns[i].offices_count; j++) {
            scanf("%d%d%d", &towns[i].offices[j].packages_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
            towns[i].offices[j].packages = malloc(sizeof(package)*towns[i].offices[j].packages_count);
            for (int k = 0; k < towns[i].offices[j].packages_count; k++) {
                towns[i].offices[j].packages[k].id = malloc(sizeof(char) * MAX_STRING_LENGTH);
                scanf("%s", towns[i].offices[j].packages[k].id);
                scanf("%d", &towns[i].offices[j].packages[k].weight);
            }
        }
    }
    int queries;
    scanf("%d", &queries);
    char town_name[MAX_STRING_LENGTH];
    while (queries--) {
        int type;
        scanf("%d", &type);
        switch (type) {
        case 1:
            scanf("%s", town_name);
            town* t = find_town(towns, towns_count, town_name);
            print_all_packages(*t);
            break;
        case 2:
            scanf("%s", town_name);
            town* source = find_town(towns, towns_count, town_name);
            int source_index;
            scanf("%d", &source_index);
            scanf("%s", town_name);
            town* target = find_town(towns, towns_count, town_name);
            int target_index;
            scanf("%d", &target_index);
            send_all_acceptable_packages(source, source_index, target, target_index);
            break;
        case 3:
            printf("Town with the most number of packages is %s\n", town_with_most_packages(towns, towns_count).name);
            break;
        }
    }
    return 0;
}


/*

10
QRZMN
3
2 6 9
xxkse
7
ksefx
3
9 5 8
wrkve
1
zeycq
7
xllnn
2
fnonu
9
hmvdm
4
lykyi
5
jhhvs
4
hjpfs
3
wbolz
7
0 2 4
RHYLY
6
4 8 10
wxywx
5
qsjbc
2
qnsbu
4
wverq
10
6 5 6
akozd
3
scfyk
2
vylku
10
cejdb
4
ijjyc
4
nppsa
8
1 6 7
aeyrq
7
3 2 4
cwxgl
6
xxruu
9
etpxo
5
10 3 10
rzodf
5
fpcsx
3
xluop
2
zetsu
3
qzzff
5
kdokr
7
szvjz
2
rqgtl
10
apbvo
1
pelnn
9
6 7 10
gfxvu
9
joyrv
7
uqnna
3
eexba
1
bcisv
9
mhztt
8
DFURO
1
4 0 6
gceyr
9
gqqbr
9
danmn
2
igbxy
5
LMFVG
2
8 0 3
ymflm
7
nanrz
2
zuvej
7
ewsbe
9
buzew
8
oszaj
2
xxnev
8
uikxf
8
5 6 6
ypgzy
5
fwjen
8
sbdoy
4
vqaur
8
weuse
4
RPMSZ
10
5 3 10
qoaax
3
klouw
10
mszmg
7
rszch
3
oeebc
10
10 9 10
gajtn
8
rujku
3
xzvwr
4
zlnqp
2
aghsb
10
wzcfg
7
smuoh
2
ohsdy
5
yzpyl
8
prnfe
7
6 2 4
tfaeg
10
iehow
9
jscue
2
znwrc
8
uhkmq
6
fybgh
8
8 4 6
eihvp
8
baoza
1
ehczx
5
iemca
5
poily
1
dkmnt
8
zpnye
10
bpups
6
5 5 9
ahrjp
3
hxupm
2
efoym
5
pguou
5
jvdpu
9
10 3 8
dttco
3
hptxj
5
sxoor
6
uujid
4
ymede
7
dmmad
4
rrmyz
3
fwbec
9
fvlxe
8
waxid
3
9 3 10
hrguz
7
dfmpv
4
pbdoh
6
lzmio
8
riwkb
8
bybve
10
yerlk
3
qbasq
1
xnvfh
6
6 1 9
taerl
2
hfhet
10
lvcdz
4
kpfkh
7
grkib
8
gwloh
4
4 4 9
cvovt
3
iyytk
4
phnph
8
wyost
7
6 2 6
jrqpr
2
ntmlq
3
lkmnj
9
crbio
9
hdobn
4
pwdbp
8
HLNNP
5
2 1 10
oiiva
10
ofwwt
9
7 0 6
rgpfd
7
qburv
7
ykujn
3
gjafd
9
twplp
3
fbrkr
2
eeutl
4
10 7 8
cowwd
2
tvhzz
3
xwuya
9
brszr
3
yawws
6
hgejm
3
unolb
10
bicio
9
heoxm
3
wvpil
2
4 6 7
slwop
5
bvtvv
4
dudlf
9
umsdn
1
6 1 10
gjoju
8
pmgym
9
jlcob
5
wxwtc
2
yobsj
6
chogo
1
RHVXT
7
5 0 1
fpngs
9
nbvda
7
hdbde
1
jjitp
5
lypiu
7
6 0 3
gobyx
10
klulf
10
pdcip
7
pmcrj
5
girez
2
uqrqc
3
3 3 6
kegxh
7
llbbe
7
mpawc
8
1 7 9
lfkxw
1
5 5 6
layyi
3
cjvgv
10
kysxg
6
nmngy
2
vvwta
6
3 1 2
bjrkx
1
cwafu
8
lluoy
7
0 0 6
FISJN
2
3 1 4
nuukk
2
gvwll
7
jpvhm
10
0 0 3
EYSPK
4
4 1 7
dtkox
4
ecwnv
2
iupsf
4
kixev
7
0 5 9
8 3 6
vjqzy
8
yguhj
10
guxhz
3
plwii
8
estld
3
lakyq
1
uqgqc
9
slrcg
7
5 4 7
dehnj
2
jkwom
7
pksje
5
xfwhi
2
zboyf
5
RVESP
4
6 5 9
ejhkg
7
tyzud
3
nghuu
7
lfxmg
9
zqdng
4
tnpkg
5
10 1 1
zyokl
1
aekfx
8
qqxmy
10
tpiot
9
cvgys
9
youse
1
saqnr
7
wnttr
3
dluzy
6
hukih
3
1 3 4
zjjdy
6
2 7 10
lateo
2
sbrym
10
1 QRZMN
1 RHYLY
1 DFURO
1 LMFVG
1 RPMSZ
1 HLNNP
1 EYSPK
1 RHVXT
1 FISJN
1 RVESP


*/

/*
10
QRZMN
3
2 6 9
xxkse
7
ksefx
3
9 5 8
wrkve
1
zeycq
7
xllnn
2
fnonu
9
hmvdm
4
lykyi
5
jhhvs
4
hjpfs
3
wbolz
7
0 2 4
RHYLY
6
4 8 10
wxywx
5
qsjbc
2
qnsbu
4
wverq
10
6 5 6
akozd
3
scfyk
2
vylku
10
cejdb
4
ijjyc
4
nppsa
8
1 6 7
aeyrq
7
3 2 4
cwxgl
6
xxruu
9
etpxo
5
10 3 10
rzodf
5
fpcsx
3
xluop
2
zetsu
3
qzzff
5
kdokr
7
szvjz
2
rqgtl
10
apbvo
1
pelnn
9
6 7 10
gfxvu
9
joyrv
7
uqnna
3
eexba
1
bcisv
9
mhztt
8
DFURO
1
4 0 6
gceyr
9
gqqbr
9
danmn
2
igbxy
5
LMFVG
2
8 0 3
ymflm
7
nanrz
2
zuvej
7
ewsbe
9
buzew
8
oszaj
2
xxnev
8
uikxf
8
5 6 6
ypgzy
5
fwjen
8
sbdoy
4
vqaur
8
weuse
4
RPMSZ
10
5 3 10
qoaax
3
klouw
10
mszmg
7
rszch
3
oeebc
10
10 9 10
gajtn
8
rujku
3
xzvwr
4
zlnqp
2
aghsb
10
wzcfg
7
smuoh
2
ohsdy
5
yzpyl
8
prnfe
7
6 2 4
tfaeg
10
iehow
9
jscue
2
znwrc
8
uhkmq
6
fybgh
8
8 4 6
eihvp
8
baoza
1
ehczx
5
iemca
5
poily
1
dkmnt
8
zpnye
10
bpups
6
5 5 9
ahrjp
3
hxupm
2
efoym
5
pguou
5
jvdpu
9
10 3 8
dttco
3
hptxj
5
sxoor
6
uujid
4
ymede
7
dmmad
4
rrmyz
3
fwbec
9
fvlxe
8
waxid
3
9 3 10
hrguz
7
dfmpv
4
pbdoh
6
lzmio
8
riwkb
8
bybve
10
yerlk
3
qbasq
1
xnvfh
6
6 1 9
taerl
2
hfhet
10
lvcdz
4
kpfkh
7
grkib
8
gwloh
4
4 4 9
cvovt
3
iyytk
4
phnph
8
wyost
7
6 2 6
jrqpr
2
ntmlq
3
lkmnj
9
crbio
9
hdobn
4
pwdbp
8
HLNNP
5
2 1 10
oiiva
10
ofwwt
9
7 0 6
rgpfd
7
qburv
7
ykujn
3
gjafd
9
twplp
3
fbrkr
2
eeutl
4
10 7 8
cowwd
2
tvhzz
3
xwuya
9
brszr
3
yawws
6
hgejm
3
unolb
10
bicio
9
heoxm
3
wvpil
2
4 6 7
slwop
5
bvtvv
4
dudlf
9
umsdn
1
6 1 10
gjoju
8
pmgym
9
jlcob
5
wxwtc
2
yobsj
6
chogo
1
RHVXT
7
5 0 1
fpngs
9
nbvda
7
hdbde
1
jjitp
5
lypiu
7
6 0 3
gobyx
10
klulf
10
pdcip
7
pmcrj
5
girez
2
uqrqc
3
3 3 6
kegxh
7
llbbe
7
mpawc
8
1 7 9
lfkxw
1
5 5 6
layyi
3
cjvgv
10
kysxg
6
nmngy
2
vvwta
6
3 1 2
bjrkx
1
cwafu
8
lluoy
7
0 0 6
FISJN
2
3 1 4
nuukk
2
gvwll
7
jpvhm
10
0 0 3
EYSPK
4
4 1 7
dtkox
4
ecwnv
2
iupsf
4
kixev
7
0 5 9
8 3 6
vjqzy
8
yguhj
10
guxhz
3
plwii
8
estld
3
lakyq
1
uqgqc
9
slrcg
7
5 4 7
dehnj
2
jkwom
7
pksje
5
xfwhi
2
zboyf
5
RVESP
4
6 5 9
ejhkg
7
tyzud
3
nghuu
7
lfxmg
9
zqdng
4
tnpkg
5
10 1 1
zyokl
1
aekfx
8
qqxmy
10
tpiot
9
cvgys
9
youse
1
saqnr
7
wnttr
3
dluzy
6
hukih
3
1 3 4
zjjdy
6
2 7 10
lateo
2
sbrym
6
10
3
1
DFURO
3
1
EYSPK
1
FISJN
2
LMFVG 0 QRZMN 2
2
RHVXT 6 RPMSZ 9
1
RHVXT
2
RHYLY 5 RHVXT 5
3



*/




