type dimension = {
  width: float,
  height: float,
};
type imageDimensions = list((string, dimension));

let getDimensionTuple = (photos: list(Decode.photo)): imageDimensions =>
  List.map(
    (photo: Decode.photo) => (
      photo.identifier,
      {width: float(photo.width), height: float(photo.height)},
    ),
    photos,
  );

type imageContainer = {
  id: string,
  dimension,
};
let getLayout =
    (
      maxHeight: float,
      res: Resolution.res,
      photos: list(Decode.photo),
      ~gap: float=0.0,
      (),
    )
    : list(list(imageContainer)) => {
  let width = res.width;

  let getHeight = (imgs: imageDimensions): float =>
    (width -. float(List.length(imgs) - 1) *. gap)
    /. List.fold_left(
         (accum, img) => {
           let (_, dimension) = img;
           accum +. dimension.width /. dimension.height;
         },
         0.0,
         imgs,
       );
  let getContainerRow = (height: float, imageDimension: (string, dimension)) => {
    let (id, dimension) = imageDimension;
    {
      dimension: {
        width: height *. dimension.width /. dimension.height,
        height,
      },
      id,
    };
  };
  let rec getRow =
          (
            (imgs, prev, containers): (
              imageDimensions,
              imageDimensions,
              list(imageContainer),
            ),
          ) =>
    switch (imgs) {
    | [head, ...tail] =>
      let next = [head, ...prev];
      let height = getHeight(next);
      if (height < maxHeight) {
        (tail, next, List.map(getContainerRow(height), next) |> List.rev);
      } else {
        getRow((tail, next, []));
      };
    | [] => (
        [],
        prev,
        List.map(getContainerRow(maxHeight), prev) |> List.rev,
      )
    };
  let rec layout =
          (
            (imgs, containers): (
              imageDimensions,
              list(list(imageContainer)),
            ),
          ) =>
    switch (imgs) {
    | [] => (imgs, containers |> List.rev)
    | [_, ..._] =>
      let (newImgs, _, container) = getRow((imgs, [], []));
      layout((newImgs, [container, ...containers]));
    };

  let (_, containers) = layout((getDimensionTuple(photos), []));
  containers;
};

let getWidth = (row: list(imageContainer), gap: float): float => {
  let width =
    List.fold_left(
      (accum, container) => accum +. container.dimension.width,
      0.0,
      row,
    );
  width +. float(List.length(row) - 1) *. gap;
};

let getHeight = (containerRow: list(imageContainer)): float =>
  switch (containerRow) {
  | [] => 0.0
  | [hd, ..._] => hd.dimension.height
  };