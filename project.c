
#include <stdio.h>

struct Product{
    int id;
    char name[30];
    float price;
};

 int main()
{
    struct Product p[20] = {
        {1, "Pen", 10},
        {2, "Notebook", 50},
        {3, "Bag", 500},
        {4, "Bottle", 150},
        {5, "Headphones", 8000}
    };

    int cart[20];
    int quantity[20];
    int productCount = 5;
    int count = 0,choice, id, qty,i, j, found;

    float total, discount, finalAmount, amount;

    FILE *fp;

    do
    {
        printf("\n----- BEST BUY -----\n");
        printf("1 Product Listing\n");
        printf("2 Add New Product\n");
        printf("3 Add to Cart\n");
        printf("4 Remove from Cart\n");
        printf("5 View Cart\n");
        printf("6 Generate Bill\n");
        printf("7 Exit\n");

        printf("Enter choice:(Integral value) ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("\nID\tProduct\t\tPrice\n");

                for(i = 0; i < productCount; i++)
                {
                    printf("%d\t%s %.2f\n",
                    p[i].id, p[i].name, p[i].price);
                }
                break;

            case 2:
                if(productCount < 20)
                {
                    p[productCount].id = productCount + 1;

                    printf("Enter Product Name: ");
                    scanf(" %s", p[productCount].name);

                    printf("Enter Product Price: ");
                    scanf("%f", &p[productCount].price);

                    if(p[productCount].price <= 0)
                    {
                        printf("Enter a valid price\n");
                        break;
                    }

                    productCount++;

                    printf("New product has been added successfully!\n");
                }
                else
                {
                    printf("List of products is full.....\n");
                }
                break;

            case 3:
                printf("Enter Product id: ");
                scanf("%d", &id);

                if(id < 1 || id > productCount)
                {
                    printf("Invalid Product id\n");
                    break;
                }

                printf("Enter Qty: ");
                scanf("%d", &qty);

                if(qty <= 0)
                {
                    printf("Invalid Qty\n");
                    break;
                }

                found = 0;

                for(i = 0; i < count; i++)
                {
                    if(cart[i] == id - 1)
                    {
                        quantity[i] = quantity[i] + qty;
                        found = 1;
                        break;
                    }
                }

                if(found == 1)
                {
                    printf("Quantity updated successfully!\n");
                }
                else if(count < 20)
                {
                    cart[count] = id - 1;
                    quantity[count] = qty;
                    count++;

                    printf("Product added to cart!\n");
                }
                else
                {
                    printf("Cart is full!\n");
                }
                break;

            case 4:
                printf("Enter Product ID to remove: ");
                scanf("%d", &id);

                found = 0;

                for(i = 0; i < count; i++)
                {
                    if(cart[i] == id - 1)
                    {
                        for(j = i; j < count - 1; j++)
                        {
                            cart[j] = cart[j + 1];
                            quantity[j] = quantity[j + 1];
                        }

                        count--;
                        found = 1;

                        printf("Product removed successfully!\n");
                        break;
                    }
                }

                if(found == 0)
                {
                    printf("Product not found!\n");
                }
                break;

            case 5:
                printf("\n===== YOUR CART =====\n");
                printf("Product\t\tQuantity\tPrice\n");

                for(i = 0; i < count; i++)
                {
                    int k = cart[i];

                    printf("%-15s\t%d\t\t%.2f\n",
                    p[k].name, quantity[i], p[k].price);
                }

                if(count == 0)
                {
                    printf("Your cart is empty!\n");
                }
                break;

            case 6:
                total = 0;

                fp = fopen("bill.txt", "w");

                if(fp == NULL)
                {
                    printf("File cannot be opened\n");
                    break;
                }

                printf("\n===== SHOPPING BILL =====\n");

                fprintf(fp, "===== SHOPPING BILL =====\n");
                fprintf(fp, "Product\t\tQuantity\tAmount\n");

                for(i = 0; i < count; i++)
                {
                    int k = cart[i];

                    amount = p[k].price * quantity[i];

                    printf("%-15s\t%d\t\t%.2f\n",
                    p[k].name, quantity[i], amount);

                    fprintf(fp, "%-15s\t%d\t\t%.2f\n",
                    p[k].name, quantity[i], amount);

                    total = total + amount;
                }

                discount = 0;

                if(total >= 1000)
                {
                    discount = total * 0.10;
                }

                finalAmount = total - discount;

                printf("-------------------------------\n");
                printf("Total: Rs. %.2f\n", total);
                printf("Discount: Rs. %.2f\n", discount);
                printf("Final Amount: Rs. %.2f\n", finalAmount);

                fprintf(fp, "-------------------------------\n");
                fprintf(fp, "Total: Rs. %.2f\n", total);
                fprintf(fp, "Discount: Rs. %.2f\n", discount);
                fprintf(fp, "Final Amount: Rs. %.2f\n", finalAmount);

                fclose(fp);

                printf("\nBill saved in bill.txt!\n");
                break;

            case 7:
                printf("Thank you for shopping with best buy XD!!!\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    }  while(choice != 7);

    return 0;
}
