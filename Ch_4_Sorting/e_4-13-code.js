/*
    Sort entry time and exit time, giving each element a score along the way
        Entry element:+1
        Exit element:-1
    Calc the partial sum of new array above and trace the time duration
        in which partial sum is largest (the most people were simultaneously present at the party)
    Return all the durations which match the conditions of the statement.
*/

class CameraData {
    constructor() {
        this.data = [];
    }
    static CameraDataEntry = class {
        constructor(name, dEntry, dExit) {
            this.person = name;
            this.dEntry = dEntry;
            this.dExit = dExit;
        }
    }
    add(name, dEntry, dExit) {
        this.data.push(new CameraData.CameraDataEntry(name, dEntry, dExit));
    }
    clear() { this.data.splice(0); }
}

function parseCmData(cmData) {
    const newData = cmData.data.reduce((acc, e) => {
        acc.push({ d: e.dEntry, score: 1 });
        acc.push({ d: e.dExit, score: -1 });
        return acc;
    }, []);
    newData.sort((a, b) => a.d - b.d);
    return newData;
}

function timeMostPresented(cmData) {
    const newData = parseCmData(cmData);
    const tracer = { attendCnt: 0, attendMax: 0, durations: [] };

    for (let i = 0; i < newData.length; i++) {
        const e = newData[i];
        if (e.score === -1) {
            if (tracer.attendMax < tracer.attendCnt) {
                tracer.attendMax = tracer.attendCnt;
                tracer.durations.splice(0);
                tracer.durations.push({ dStt: newData[i - 1].d, dEnd: e.d });
            } else if (tracer.attendMax === tracer.attendCnt) {
                tracer.durations.push({ dStt: newData[i - 1].d, dEnd: e.d });
            }
        }
        tracer.attendCnt += e.score;
    }
    return tracer.durations;
}

function main() {
    let cmData = new CameraData();
    cmData.add("p1", new Date(2020, 6, 1, 10, 0), new Date(2020, 6, 1, 10, 20));
    cmData.add("p2", new Date(2020, 6, 1, 10, 25), new Date(2020, 6, 1, 10, 45));
    let durations = timeMostPresented(cmData);
    console.assert(durations.length === 2);
    console.assert(durations[0].dStt.getTime() === new Date(2020, 6, 1, 10, 0).getTime());
    console.assert(durations[0].dEnd.getTime() === new Date(2020, 6, 1, 10, 20).getTime());
    console.assert(durations[1].dStt.getTime() === new Date(2020, 6, 1, 10, 25).getTime());
    console.assert(durations[1].dEnd.getTime() === new Date(2020, 6, 1, 10, 45).getTime());

    cmData.add("p3", new Date(2020, 6, 1, 11, 1), new Date(2020, 6, 1, 12, 0));
    cmData.add("p4", new Date(2020, 6, 1, 11, 21), new Date(2020, 6, 1, 12, 20));
    cmData.add("p5", new Date(2020, 6, 1, 11, 41), new Date(2020, 6, 1, 12, 40));
    cmData.add("p6", new Date(2020, 6, 1, 12, 1), new Date(2020, 6, 1, 13, 0));
    cmData.add("p7", new Date(2020, 6, 1, 12, 21), new Date(2020, 6, 1, 13, 20));
    cmData.add("p8", new Date(2020, 6, 1, 12, 41), new Date(2020, 6, 1, 13, 40));
    durations = timeMostPresented(cmData);
    console.assert(durations.length === 4);
    console.assert(durations[0].dStt.getTime() === new Date(2020, 6, 1, 11, 41).getTime());
    console.assert(durations[0].dEnd.getTime() === new Date(2020, 6, 1, 12, 0).getTime());
    console.assert(durations[1].dStt.getTime() === new Date(2020, 6, 1, 12, 1).getTime());
    console.assert(durations[1].dEnd.getTime() === new Date(2020, 6, 1, 12, 20).getTime());
    console.assert(durations[2].dStt.getTime() === new Date(2020, 6, 1, 12, 21).getTime());
    console.assert(durations[2].dEnd.getTime() === new Date(2020, 6, 1, 12, 40).getTime());
    console.assert(durations[3].dStt.getTime() === new Date(2020, 6, 1, 12, 41).getTime());
    console.assert(durations[3].dEnd.getTime() === new Date(2020, 6, 1, 13, 0).getTime());

    cmData.clear();
    cmData.add("p9", new Date(2020, 6, 1, 11, 1), new Date(2020, 6, 1, 14, 40));
    cmData.add("p10", new Date(2020, 6, 1, 11, 21), new Date(2020, 6, 1, 14, 20));
    cmData.add("p11", new Date(2020, 6, 1, 11, 41), new Date(2020, 6, 1, 14, 0));
    cmData.add("p12", new Date(2020, 6, 1, 12, 1), new Date(2020, 6, 1, 13, 40));
    cmData.add("p13", new Date(2020, 6, 1, 12, 21), new Date(2020, 6, 1, 13, 20));
    cmData.add("p14", new Date(2020, 6, 1, 12, 41), new Date(2020, 6, 1, 13, 0));
    durations = timeMostPresented(cmData);
    console.assert(durations.length === 1);
    console.assert(durations[0].dStt.getTime() === new Date(2020, 6, 1, 12, 41).getTime());
    console.assert(durations[0].dEnd.getTime() === new Date(2020, 6, 1, 13, 0).getTime());
}

main();