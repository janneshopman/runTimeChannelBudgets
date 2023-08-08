    fileName path(UMean.rootPath()/UMean.caseName()/"graphs"/UMean.instance());
    mkDir(path);

    scalarField uxMeanvalues
    (
        channelIndexing.collapse(UMean.component(vector::X)())
    );

    scalarField uxpuxpMeanValues(channelIndexing.collapse(uxpuxpMean));
    scalarField uypuypMeanValues(channelIndexing.collapse(uypuypMean));
    scalarField uzpuzpMeanValues(channelIndexing.collapse(uzpuzpMean));
    scalarField uxpuypMeanValues(channelIndexing.collapse(uxpuypMean, true));

    scalarField convValues(channelIndexing.collapse(conv));
    scalarField prodValues(channelIndexing.collapse(prod));

    scalarField diffValues(channelIndexing.collapse(diff));
    scalarField dissValues(channelIndexing.collapse(diss));

    scalarField pDiffValues(channelIndexing.collapse(pDiff));

    scalarField uxRMSValues(sqrt(mag(uxpuxpMeanValues)));
    scalarField uyRMSValues(sqrt(mag(uypuypMeanValues)));
    scalarField uzRMSValues(sqrt(mag(uzpuzpMeanValues)));

    scalarField kValues
    (
        0.5*(sqr(uxRMSValues) + sqr(uyRMSValues) + sqr(uzRMSValues))
    );

    scalarField transValues(convValues - prodValues);
    scalarField vDiffValues(diffValues - dissValues);

    const scalarField& y = channelIndexing.y();

    makeGraph(y, uxMeanvalues, "uxMean", path, gFormat);
    makeGraph(y, uxRMSValues, "uxRMS", path, gFormat);
    makeGraph(y, uyRMSValues, "uyRMS", path, gFormat);
    makeGraph(y, uzRMSValues, "uzRMS", path, gFormat);
    makeGraph(y, uxpuypMeanValues, "uxpuypMean", path, gFormat);
    makeGraph(y, kValues, "k", path, gFormat);
    makeGraph(y, prodValues, "prod", path, gFormat);
    makeGraph(y, transValues, "trans", path, gFormat);
    makeGraph(y, dissValues, "diss", path, gFormat);
    makeGraph(y, vDiffValues, "vDiff", path, gFormat);
    makeGraph(y, pDiffValues, "pDiff", path, gFormat);
