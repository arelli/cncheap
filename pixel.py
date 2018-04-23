from PIL import Image
im = Image.open("image.png")
pix = im.load()
width, height=im.size
imageArray=[]
for i in range(height):
    imageArray.append([])
    for ii in range(width):
        r,g,b = pix[height,width]
        if (r+g+b)<(255*3/2):
            imageArray[height].append(0)
        elif (r+g+b)>(255*3/2):
            imageArray[height].append(1)
for i in range(height):
    for ii in range(witdh):
        print(imageArray[height][width])
    print("/n")
         






