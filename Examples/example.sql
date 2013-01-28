-- Simple query:

SELECT booking.EmailAddress, booking1.FirstName, booking2.LastName, 
    booking3.Address, booking4.Phone, booking.`Date`, 
    booking.Number

FROM booking, booking booking1, booking booking2, booking booking3, 
    booking booking4

GROUP BY booking.EmailAddress, booking1.FirstName, 
    booking2.LastName, booking3.Address, booking4.Phone, 
    booking.`Date`, booking.Number

HAVING (booking.Number > 15293)

ORDER BY booking.EmailAddress, booking1.FirstName DESC